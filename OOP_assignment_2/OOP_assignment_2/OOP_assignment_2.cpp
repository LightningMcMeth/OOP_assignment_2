#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

struct Product {
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
            Product product;
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

    const std::vector<Product>& getProducts() const {
        return products;
    }

private:
    std::vector<Product> products;
};


int main()
{
    ConfigReader configReader("test.txt");
    std::vector<Product> products = configReader.getProducts();

    return 0;
}