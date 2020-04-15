from banking import Bank 

def main():
    print("Creating bank")
    bank = Bank()
    print("Creating account")
    bank.create_account("bill gates", 100)
    print("Checking balance")
    result = bank.check_balance("jeff bezos")
    print(result)
    result = bank.check_balance("bill gates")
    print(result)
    result = bank.deposit("bill gates", 10)
    print(result)
    result = bank.withdraw("bill gates", 15)
    print(result)
    result = bank.withdraw("bill gates", 1000)
    print(result)

if __name__=="__main__":
    main()
