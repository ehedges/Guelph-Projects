all: targ1 targ2 targ3 targ4 targ5

targ1:
	python -m pytest -v -k "not Fail" test_functions.py
targ2:
	python -m pytest -v test_functions.py::test_productNumbers		
targ3:
	python -m pytest -v -m Target3 test_functions.py	
targ4:
	python -m pytest -v -m Target4 test_functions.py
targ5:
	python -m pytest -v --maxfail=2  test_functions.py