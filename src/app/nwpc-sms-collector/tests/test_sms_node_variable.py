import os
import sys
sys.path.append(os.path.join(os.path.dirname(__file__), "../"))
from sms_node_variable import SmsNodeVariable, get_sms_node_from_cdp_output


class TestSmsNode(object):
    def test_normal_suite_cdp_output(self):
        with open("./data/normal_suite_cdp.txt") as f:
            cdp_output = f.readlines()
            node = get_sms_node_from_cdp_output(cdp_output)
            assert node.get_variable_value('SUITE') == 'grapes_meso_v4_1'
            assert node.get_variable_value('DATE') == '15.01.2017'
            assert node.get_variable_value('DAY') == 'sunday'
            assert node.get_variable_value('DD') == '15'

            assert node.get_variable_value('SMSOUT') == '/cma/g1/nwp/SMSOUT'
            assert node.get_variable_value('SMSHOME') == '/cma/g1/nwp/SMSOUT'
            assert node.get_variable_value('VERSION') == '_v4_1'

    def test_normal_family_cdp_output(self):
        with open("./data/normal_family_cdp.txt") as f:
            cdp_output = f.readlines()
            node = get_sms_node_from_cdp_output(cdp_output)
            assert node.get_variable_value('FAMILY') == 'cold'
            assert node.get_variable_value('FAMILY1') == 'cold'

            assert node.get_variable_value('SMSINCLUDE') == '/cma/u/nwp/smsworks/def/grapes_meso/include'
            assert node.get_variable_value('SMSFILES') == '/cma/u/nwp/smsworks/def/grapes_meso/smsfiles'

    def test_error_login_cdp(self):
        with open("./data/error_login_cdp.txt") as f:
            cdp_output = f.readlines()
            node = get_sms_node_from_cdp_output(cdp_output)
            assert node is None

    def test_error_node_path_cdp(self):
        with open("./data/error_node_path_cdp.txt") as f:
            cdp_output = f.readlines()
            node = get_sms_node_from_cdp_output(cdp_output)
            assert node is None

    def test_error_sms_server_cdp(self):
        with open("./data/error_sms_server_cdp.txt") as f:
            cdp_output = f.readlines()
            node = get_sms_node_from_cdp_output(cdp_output)
            assert node is None
