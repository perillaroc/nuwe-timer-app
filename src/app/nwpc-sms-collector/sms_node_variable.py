class SmsNodeVariableType(object):
    Variable = 0
    GeneratedVariable = 1


class SmsNodeVariable(object):
    def __init__(self, variable_type, name, value):
        self.name = name
        self.variable_type = variable_type
        self.value = value


class SmsNode(object):
    def __init__(self):
        self.variable_list = []
        self.generated_variable_list = []
        self.name = ''
        self.status = None
        self.node_type = None


def get_sms_node_from_cdp_output(cdp_output):
    # find status
    cur_line_no = 0
    line_count = len(cdp_output)

    while cur_line_no < line_count:
        line = cdp_output[cur_line_no]
        if len(line) > 0 and line.startswith('/') and not line.startswith('/-CDP'):
            break
        cur_line_no += 1
    if cur_line_no == line_count:
        return None

    # find show
    while cur_line_no < line_count:
        line = cdp_output[cur_line_no]
        if line == '\n':
            break
        cur_line_no += 1

    cur_line_no += 1
    if cur_line_no >= line_count:
        return None

    line = cdp_output[cur_line_no]
    if line[0].startswith('#'):
        return None

    start_line_no = cur_line_no

    cur_line_no += 1
    end_line_no = -1
    while cur_line_no < line_count:
        line = cdp_output[cur_line_no]
        if not line.startswith('  '):
            end_line_no = cur_line_no
            break
        cur_line_no += 1

    if end_line_no == -1:
        return None

    # get variables
    node_line = cdp_output[start_line_no: end_line_no]
    node = SmsNode()
    tokens = node_line[0].strip().split(' ')
    if len(tokens) > 5:
        node.node_type = tokens[0]
        node.name = tokens[1]
        node.status = tokens[4]

    for line in node_line[1:]:
        line = line.strip()
        if line.startswith('# genvar '):
            index = line.find(' ', 9)
            if index == -1:
                continue
            variable_name = line[9:index]
            variable_value = line[index+1:]
            if variable_value[0] == '\'' and variable_value[-1]=='\'':
                variable_value = variable_value[1:-1]
            variable = SmsNodeVariable(
                SmsNodeVariableType.GeneratedVariable,
                variable_name,
                variable_value
            )
            node.generated_variable_list.append(variable)
        elif line.startswith('edit '):
            index = line.find(' ', 5)
            if index == -1:
                continue
            variable_name = line[5:index]
            variable_value = line[index + 1:]
            if variable_value[0] == '\'' and variable_value[-1] == '\'':
                variable_value = variable_value[1:-1]
            variable = SmsNodeVariable(
                SmsNodeVariableType.Variable,
                variable_name,
                variable_value
            )
            node.variable_list.append(variable)
        else:
            pass

    return node


def main():
    pass


if __name__ == "__main__":
    main()
