#pragma once

#include <QRunnable>
#include <QFutureInterface>
#include <QFuture>

#include <utility>
#include <tuple>
#include <type_traits>

QT_BEGIN_NAMESPACE
class QThreadPool;
QT_END_NAMESPACE

namespace ProgressUtil{

class ShellCommand;

template <typename Function, typename... Args>
void runFunction(QFutureInterface<void> future_interface, Function &&function, Args&&... args)
{
    function(future_interface, std::forward<Args>(args)...);
}

template <typename Function>
class ClassMemberFunction;


template <typename Object, typename... Args>
class ClassMemberFunction<void (Object::*)(Args...) const>
{
public:
    ClassMemberFunction(void (Object::* function)(Args...) const, const Object *object):
        function_{function},
        object_{object}
    {}

    void operator ()(Args&&... args) const
    {
        return ((*object_).*function_)(std::forward<Args>(args)...);
    }

private:
    void (Object::* function_)(Args...) const;
    const Object *object_;
};

template <typename Object, typename... Args>
class ClassMemberFunction<void (Object::*)(Args...)>
{
public:
    ClassMemberFunction(void (Object::* function)(Args...), Object *object):
        function_{function},
        object_{object}
    {}

    void operator ()(Args&&... args) const
    {
        return ((*object_).*function_)(std::forward<Args>(args)...);
    }

private:
    void (Object::* function_)(Args...);
    Object *object_;
};

template <typename Function, typename Object, typename... Args,
          typename = std::enable_if<
              std::is_member_pointer<
                  typename std::decay<Function>::type
              >::value
          >::type
>
void runDispatch(QFutureInterface<void> future_interface, Function &&function, Object &&object, Args&&... args)
{
    runFunction(future_interface,
                ClassMemberFunction<typename std::decay<Function>::type>{
                    std::forward<Function>(function),
                    std::forward<Object>(object)},
                std::forward<Args>(args)...);
}

template <typename Function, typename... Args,
          typename = std::enable_if<
              !std::is_member_pointer<
                  typename std::decay<Function>::type
              >::value
          >::type
>
void runDispatch(QFutureInterface<void> future_interface, Function &&function, Args&&... args)
{
    runFunction(future_interface,
                std::forward<Function>(function),
                std::forward<Args>(args)...);
}


template <typename Function, typename... Args>
class AsyncRunJob: public QRunnable
{
public:
    AsyncRunJob(Function &&function, Args&&... args):
        data_{std::forward<Function>(function), std::forward<Args>(args)...}
    {
        future_interface_.setRunnable(this);
        future_interface_.reportStarted();
        future_interface_.setThreadPool(QThreadPool::globalInstance());
        future_interface_.setProgressRange(0, 100);
    }

    ~AsyncRunJob()
    {
        future_interface_.reportFinished();
    }

    void setPool(QThreadPool *pool)
    {
        future_interface_.setThreadPool(pool);
    }

    void run() override
    {
        constexpr auto Size = std::tuple_size< Data >::value;
        runInner(std::make_index_sequence<Size>::type());
    }

    QFuture<void> future()
    {
        return future_interface_.future();
    }

private:
    using Data = std::tuple<Function, Args... >;
    template <size_t... index>
    void runInner(std::index_sequence<index...>)
    {
        runDispatch(future_interface_, std::move(std::get<index>(data_))...);
    }

    QFutureInterface<void> future_interface_;
    Data data_;
};

template <typename Function, typename... Args>
QFuture<void> runAsyncJob(Function &&function, Args&&... args)
{
    QThreadPool *pool = QThreadPool::globalInstance();
    auto async_job = new AsyncRunJob<Function, Args...>{std::forward<Function>(function), std::forward<Args>(args)...};
    QFuture<void> future = async_job->future();
    pool->start(async_job);
    return future;
}

}
