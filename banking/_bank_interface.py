"""Internal interface to the C code."""
from ctypes import POINTER, Structure, c_char_p, c_int, c_void_p, cdll
import os


_BANK_PATH = os.path.join(os.path.dirname(__file__), "libbanking.so")
_BANKING_LIB = cdll.LoadLibrary(_BANK_PATH)


def encode_text(text: str) -> c_char_p:
    """Encode some text for use in the C code."""
    encoded_text = text.encode(encoding="utf-8")
    return c_char_p(encoded_text)


class RECEIPT(Structure):
    """C Struct for a transaction receipt."""

    _fields_ = [("status", c_int), ("cash_returned", c_int), ("balance", c_int)]


class BANKING_HANDLER(Structure):
    """C struct for a handler to the backend code."""

    _fields_ = [
        ("bank", c_void_p),
    ]


_BANKING_LIB.createBank.argtypes = []
_BANKING_LIB.createBank.restype = POINTER(BANKING_HANDLER)
_BANKING_LIB.destroyBank.argtypes = [POINTER(BANKING_HANDLER)]
_BANKING_LIB.destroyBank.restype = None
_BANKING_LIB.createAccount.argtypes = [POINTER(BANKING_HANDLER), c_char_p, c_char_p, c_int]
_BANKING_LIB.createAccount.restype = RECEIPT
_BANKING_LIB.checkBalance.argtypes = [POINTER(BANKING_HANDLER), c_char_p, c_char_p]
_BANKING_LIB.checkBalance.restype = RECEIPT
_BANKING_LIB.deposit.argtypes = [POINTER(BANKING_HANDLER), c_char_p, c_char_p, c_int]
_BANKING_LIB.deposit.restype = RECEIPT
_BANKING_LIB.withdraw.argtypes = [POINTER(BANKING_HANDLER), c_char_p, c_char_p, c_int]
_BANKING_LIB.withdraw.restype = RECEIPT

CREATE_BANK_FN = _BANKING_LIB.createBank
DESTROY_BANK_FN = _BANKING_LIB.destroyBank
CREATE_ACCOUNT_FN = _BANKING_LIB.createAccount
CHECK_BALANCE_FN = _BANKING_LIB.checkBalance
DEPOSIT_FN = _BANKING_LIB.deposit
WITHDRAW_FN = _BANKING_LIB.withdraw

STATUS_SUCCESS = _BANKING_LIB.SUCCESS
STATUS_AUTH_FAILED = _BANKING_LIB.AUTH_FAILED
STATUS_INSUFFICIENT_FUNDS = _BANKING_LIB.INSUFFICIENT_FUNDS
STATUS_OTHER_ERROR = _BANKING_LIB.OTHER_ERROR
