source_base_dir = $$PWD

sub_dir = $$_PRO_FILE_PWD_
sub_dir ~= s,^$$re_escape($$PWD),,
build_base_dir = $$clean_path($$OUT_PWD)
build_base_dir ~= s,$$re_escape($$sub_dir)$,,


build_lib_dir = $$build_base_dir/lib
build_plugins_dir = $$build_base_dir/plugins
build_vendor_dir = $$build_base_dir/vendor

python_env_dir = $${source_base_dir}/../playground/python/python36-x64
