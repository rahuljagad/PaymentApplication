#include <iostream>

//Is there a reason to templatize this class ?
class Wallet {
    public:
        Wallet();
	~Wallet(){ }

    protected:
        uint64_t fWalletId; //unique wallet id.
        uint64_t fBalance;  //unique Balance
};
