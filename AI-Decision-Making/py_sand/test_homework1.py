import pytest
import pickle
from homework1 import *

f = open('data.pck', 'rb')
tests = pickle.load(f)
f.close()


@pytest.mark.parametrize('inp, expected', [i for i in tests['q1']])
def test_q1(inp, expected):
    assert q1(inp) == pytest.approx(expected, 0.005)


@pytest.mark.parametrize('inp, expected', [i for i in tests['q2']])
def test_q2(inp, expected):
    assert q2(inp) == pytest.approx(expected, 0.0000005)


@pytest.mark.parametrize('inp, expected', [i for i in tests['q3']])
def test_q3(inp, expected):
    assert q3(inp) == pytest.approx(expected, 0.0005)
