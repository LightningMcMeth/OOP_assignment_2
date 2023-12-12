#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

struct ProductData {
    std::string type;
    std::string name;
    float price = 0;
    int quantity = 0;
    std::vector<std::string> additionalAttr;
};

class ConfigReader {
public:
    ConfigReader(const std::string& filename) {

        std::ifstream file(filename);
        std::string line;

        if (!file.is_open()) {

            std::cerr << "Failed to open file :(\n";
            return;
        }

        while (getline(file, line)) {

            if (line.empty() || line[0] == '#') {
                continue;
            }

            std::istringstream gamer(line);
            ProductData product;
            std::string attrToken;

            getline(gamer, product.type, ',');
            getline(gamer, product.name, ',');

            gamer >> product.price;
            gamer.ignore();
            gamer >> product.quantity;
            gamer.ignore();

            while (getline(gamer, attrToken, ',')) {
                product.additionalAttr.push_back(attrToken);
            }

            products.push_back(product);
        }
    }

    const std::vector<ProductData>& getProducts() const {
        return products;
    }

private:
    std::vector<ProductData> products;
};

class Product {
public:

    Product(int ID, const std::string& name, float price, int quantity) : productID(ID), name(name), price(price), qttyInStock(quantity){}

    int getProductID() const { return productID; }
    std::string getName() const { return name; }
    float getPrice() const { return price; }
    int getQuantityInStock() const { return qttyInStock; }

    void setProductID(int id) { productID = id; }
    void setName(const std::string& newName) { name = newName; }
    void setPrice(float newPrice) { price = newPrice; }
    void setQuantityInStock(int newQuantity) { qttyInStock = newQuantity; }

    float calculateTotalCost() const {
        return price * qttyInStock;
    }

    virtual ~Product() = default;

protected:
    int productID = 0;
    std::string name;
    float price = 0;
    int qttyInStock;
};

class Electronics : public Product {
public:

    Electronics(int ID, const std::string& name, float price, int quantity, const std::string& brand, const std::string& model, int power)
        : Product(ID, name, price, quantity), brand(brand), model(model), powerConsumption(power){}

    std::string getBrand() const { return brand; }
    std::string getModel() const { return model; }
    int getPowerConsumption() const { return powerConsumption; }

private:
    std::string brand;
    std::string model;
    int powerConsumption = 0;
};

class Clothing : public Product {
public:
    Clothing(int ID, const std::string& name, float price, int quantity, const std::string& size, const std::string& color, const std::string& material)
        : Product(ID, name, price, quantity), size(size), color(color), material(material){}

    std::string getSize() const { return size; }
    std::string getColor() const { return color; }
    std::string getMaterial() const { return material; }

private:
    std::string size;
    std::string color;
    std::string material;
};

class Inventory {
public:

    Inventory(){}

    void setProducts(const std::vector<ProductData>& newProducts) {

        for (const auto& productData : newProducts) {
            addProduct(productData);
        }
    }

    void listProducts() {

        for (const auto& productPair : products) {
            std::cout << "\n\n" << productPair.first << ":\n\n";

            for (const auto& productPtr : productPair.second) {

                auto elecPtr = std::dynamic_pointer_cast<Electronics>(productPtr);
                auto clothPtr = std::dynamic_pointer_cast<Clothing>(productPtr);

                if (elecPtr) {
                    std::cout << "ID: " << elecPtr->getProductID() << " - " << elecPtr->getName() << " - $" << elecPtr->getPrice()
                        << " - " << elecPtr->getBrand() << " - " << elecPtr->getModel() << " - "
                        << elecPtr->getPowerConsumption() << "W - in stock: " << elecPtr->getQuantityInStock() << '\n';
                }
                else if (clothPtr) {
                    std::cout << "ID: " << clothPtr->getProductID() << " - " << clothPtr->getName() << " - $" << clothPtr->getPrice()
                        << " - " << clothPtr->getSize() << " - " << clothPtr->getColor() << " - "
                        << clothPtr->getMaterial() << " - in stock: " << clothPtr->getQuantityInStock() << '\n';
                }
            }
        }
    }

private:
    std::map<std::string, std::vector<std::shared_ptr<Product>>> products;
    int ID = 0;
    int stockThreshhold = 3;

    void addProduct(const ProductData& productData) {

        if (productData.type == "Electronics") {

            if (productData.additionalAttr.size() >= 3) {

                products[productData.type].push_back(std::make_shared<Electronics>(
                ID,
                productData.name,
                productData.price,
                productData.quantity,
                productData.additionalAttr[0],
                productData.additionalAttr[1],
                stoi(productData.additionalAttr[2])));
            }
            else {
                std::cout << "err: Not enough product attributes.\n";
            }
        }
        else if (productData.type == "Clothing") {

            if (productData.additionalAttr.size() >= 3) {

                products[productData.type].push_back(std::make_shared<Clothing>(
                ID,
                productData.name,
                productData.price,
                productData.quantity,
                productData.additionalAttr[0],
                productData.additionalAttr[1],
                productData.additionalAttr[2]));
            }
            else {
                std::cout << "err: Not enough product attributes.\n";
            }
        }
        else {
            std::cout << "err: " << productData.type << ": Unkown product type.\n";
        }

        ID++;
    }
};



class UI {
public:


private:
    std::vector<std::shared_ptr<Product>> boughtProducts;
};



int main()
{
    ConfigReader configReader("test.txt");
    Inventory inventory;
    UI interface;

    std::string commandType;

    inventory.setProducts(configReader.getProducts());

    while (true) {
        std::cin.ignore();

        std::cout << "\n\nEnter your command (buy, view, return, list): ";
        std::cin >> commandType;
        std::cout << '\n';

        if (commandType == "list") {

            inventory.listProducts();
        }
        else if (commandType == "buy") {

        }
        else if (commandType == "return") {

        }
        else if (commandType == "view") {

        }
        else if (commandType == "exit") {

            return 0;
        }
        else {
            std::cout << "Unknown command.\n";
        }
    }

    return 0;
}