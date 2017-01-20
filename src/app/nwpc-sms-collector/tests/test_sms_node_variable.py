import os
import sys
sys.path.append(os.path.join(os.path.dirname(__file__), "../"))
from sms_node_variable import SmsNodeVariable, get_sms_node_from_cdp_output


def test_get_var_list_from_cdp_output():
    with open("./data/error_login_cdp.txt") as f:
        cdp_output = f.readlines()
        result = get_sms_node_from_cdp_output(cdp_output)
        print(result)
