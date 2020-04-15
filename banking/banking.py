"""Public python interface."""
import enum
from typing import NamedTuple

from . import _bank_interface


class StatusCode(enum.Enum):
    """Enum to represent the return status codes."""

    Success = _bank_interface.STATUS_SUCCESS
    AuthFailed = _bank_interface.STATUS_AUTH_FAILED
    InsufficientFunds = _bank_interface.STATUS_INSUFFICIENT_FUNDS
    OtherError = _bank_interface.STATUS_OTHER_ERROR


class Receipt(NamedTuple):
    """Transaction receipt."""

    status_code: StatusCode
    cash_returned: int
    balance: int


class Bank:
    def __init__(self) -> None:
        """Handler for banking operations."""
        self.handler = _bank_interface.CREATE_BANK_FN()

    def __del__(self) -> None:
        """Clear any memory associated with the data structures."""
        _bank_interface.DESTROY_BANK_FN(self.handler)

    def create_account(self, username: str, balance: int) -> Receipt:
        """Create a new account with a given balance."""
        receipt = _bank_interface.CREATE_ACCOUNT_FN(
            self.handler, _bank_interface.encode_username(username), balance
        )
        result = Receipt(
            status_code=receipt.status,
            cash_returned=receipt.cash_returned,
            balance=receipt.balance,
        )
        return result

    def check_balance(self, username: str) -> Receipt:
        """Check the balance of an account."""
        receipt = _bank_interface.CHECK_BALANCE_FN(
            self.handler, _bank_interface.encode_username(username)
        )
        result = Receipt(
            status_code=receipt.status,
            cash_returned=receipt.cash_returned,
            balance=receipt.balance,
        )
        return result

    def deposit(self, username: str, value: int) -> Receipt:
        """Deposit some money into an account."""
        receipt = _bank_interface.DEPOSIT_FN(
            self.handler, _bank_interface.encode_username(username), value
        )
        result = Receipt(
            status_code=receipt.status,
            cash_returned=receipt.cash_returned,
            balance=receipt.balance,
        )
        return result

    def withdraw(self, username: str, value: str) -> Receipt:
        """Withdraw some money from an account."""
        receipt = _bank_interface.WITHDRAW_FN(
            self.handler, _bank_interface.encode_username(username), value
        )
        result = Receipt(
            status_code=receipt.status,
            cash_returned=receipt.cash_returned,
            balance=receipt.balance,
        )
        return result
