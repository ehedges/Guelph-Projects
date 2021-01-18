##name: Patrick Di Salvo
##Date: November 1st 2nd 2019


import functions
import pytest

##This function defintion is complete, use it as a guideline for completing
##the rest of the functio defintions
@pytest.mark.Target4
def test_addNumbers():
    assert functions.add(2, 3) == 5


##Complete this function
@pytest.mark.Target4
def test_productNumbers():
    assert functions.product(2, 3) == 6
    return


##Complete this function
def test_addNumbersFail():
    assert functions.add(2, 3) == 9
    return
##Complete this function

def test_productNumbersFail():
    assert functions.product(2, 3) == 9
    return
##Complete this function
@pytest.mark.Target3
def test_addStrings():
    assert functions.add("Mary ","Lou") == "Mary Lou"
    return
##Complete this function
@pytest.mark.Target3
def test_productStrings():
    assert functions.product("Mary ", 3) == "Mary Mary Mary "
    return
##Complete this function

def tes_subtractNumbers():
    assert functions.subtract(6, 4) == 2
    return
##Complete this function such that it will be skipped when running the test
def test_skip():
    assert functions.subtract(9, 3) == 6
    


