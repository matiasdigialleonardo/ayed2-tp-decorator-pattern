    private:
        std::string name;
        int quantity;

    public:
        Item(std::string name, int quantity) : name(name), quantity(quantity) {}

        std::unordered_map<std::string, int> GetItemQuantities() override {
            std::unordered_map<std::string, int> itemQuantity;
            itemQuantity[name] = quantity;
            return itemQuantity;
        }