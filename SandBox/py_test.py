py = "[python]"
print(py,"called print from py_test.py")

import pixel_engine as pe

t = pe.T();
t.x = 3;
tuser = pe.Tuser();

ans = tuser.callWithT(t);
print(py, "ans =", ans.x)

def func():
	print(py,"func called")