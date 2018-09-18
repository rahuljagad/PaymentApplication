#include <iostream>

class Wallet {
    public:
        Wallet();
	~Wallet(){ }

    protected:
        uint64_t fWalletId; //unique wallet id.
        uint64_t fBalance;  //unique Balance
};
