from banking import Bank 

def main():
    print("Creating bank")
    bank = Bank()
    print("Creating account")
    bank.create_account("bill gates", "msft", 100)
    print("Checking balance")
    result = bank.check_balance("jeff bezos", "amzn")
    print(result)
    result = bank.check_balance("bill gates", "msft")
    print(result)
    result = bank.deposit("bill gates", "msft", 10)
    print(result)
    result = bank.withdraw("bill gates", "msft", 15)
    print(result)
    result = bank.withdraw("bill gates", "msft", 1000)
    print(result)

if __name__=="__main__":
    main()
