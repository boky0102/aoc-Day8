#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>

struct coor {
    int x;
    int y;
};

int factoria(int n){
    int res = 1;
    for(int i = 1; i <= n; i++){
        res *= i;
    }
    return res;
}

std::vector<std::pair<coor, coor>> generateCombinations(const std::vector<coor> &elements){
    auto n = elements.size();
    int cmbN = factoria(n) / 2;
    std::unordered_set<std::string> combinations;

    std::vector<std::pair<coor,coor>> combPairs;
    combPairs.reserve(cmbN);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i != j){
                auto currComb = std::to_string(i) + std::to_string(j);
                std::sort(currComb.begin(), currComb.end());
                auto inserted = combinations.emplace(currComb);
                if(inserted.second){
                    combPairs.emplace_back(elements[i], elements[j]);
                }
            }
        }
    }

    std::cout << "-------------------\n";

    for(const auto& set: combPairs){
        std::cout << "X "<< set.first.x << ", Y " << set.first.y << " X "<< set.second.x << ", Y " << set.second.y;
        std::cout << "\n";
    }

    std::cout << "-------------------\n";

    return combPairs;

}

bool withinBounds(int width, int height, coor cord){
    if(cord.x >= 0 && cord.x <= width && cord.y >= 0 && cord.y <= height){
        return true;
    }
    return false;
}

bool topRight(int xDiff, int yDiff , std::pair<coor,coor> link){
    if(link.first.x + xDiff == link.second.x && link.first.y + yDiff == link.second.y){
        if(link.second.x - xDiff == link.first.x && link.second.y - yDiff == link.first.y){
            return true;
        }
    }
    return false;
}

bool bottomRight(int xDiff, int yDiff , std::pair<coor,coor> link){
    if(link.first.x - xDiff == link.second.x && link.first.y - yDiff == link.second.y){
        if(link.second.x + xDiff == link.first.x && link.second.y + yDiff == link.first.y){
            return true;
        }
    }
    return false;
}

bool bottomLeft(int xDiff, int yDiff , std::pair<coor,coor> link){
    if(link.first.x - xDiff == link.second.x && link.first.y + yDiff == link.second.y){
        if(link.second.x + xDiff == link.first.x && link.second.y - yDiff == link.first.y){
            return true;
        }
    }
    return false;
}

bool topLeft(int xDiff, int yDiff , std::pair<coor,coor> link){
    if(link.first.x + xDiff == link.second.x && link.first.y - yDiff == link.second.y){
        if(link.second.x - xDiff == link.first.x && link.second.y + yDiff == link.first.y){
            return true;
        }
    }
    return false;
}




void createAntiNode(std::pair<coor, coor> &link, std::vector<std::string> &network){
    auto width = network[0].size() - 1;
    auto height = network.size() - 1;

    auto xDiff = abs(link.first.x - link.second.x);
    auto yDiff = abs(link.first.y - link.second.y);

//    auto diffx = link.first.x - link.second.x;
//    auto diffy = link.first.y - link.second.y;

    coor anFirst;
    coor anSecond;

    if(topRight(xDiff, yDiff, link)){
        int x = link.first.x - xDiff;
        int y = link.first.y - yDiff;
        int x2 = link.second.x + xDiff;
        int y2 = link.second.y + yDiff;
        while((withinBounds(width, height, coor(x, y)))){
            network[y][x] = '#';
            x = x - xDiff;
            y = y - yDiff;
        }

        while(withinBounds(width, height, coor(x2, y2))){
            network[y2][x2] = '#';
            x2 = x2 + xDiff;
            y2 = y2 + yDiff;
        }
    }

    if(bottomRight(xDiff, yDiff, link)){
        int x = link.first.x + xDiff;
        int y = link.first.y + yDiff;
        int x2 = link.second.x - xDiff;
        int y2 = link.second.y - yDiff;
        while((withinBounds(width, height, coor(x, y)))){
            network[y][x] = '#';
            x = x + xDiff;
            y = y + yDiff;
        }

        while(withinBounds(width, height, coor(x2, y2))){
            network[y2][x2] = '#';
            x2 = x2 - xDiff;
            y2 = y2 - yDiff;
        }
    }

    if(bottomLeft(xDiff, yDiff, link)){
        int x = link.first.x + xDiff;
        int y = link.first.y - yDiff;
        int x2 = link.second.x - xDiff;
        int y2 = link.second.y + yDiff;
        while((withinBounds(width, height, coor(x, y)))){
            network[y][x] = '#';
            x = x + xDiff;
            y = y - yDiff;
        }

        while(withinBounds(width, height, coor(x2, y2))){
            network[y2][x2] = '#';
            x2 = x2 - xDiff;
            y2 = y2 + yDiff;
        }
    }

    if(topLeft(xDiff, yDiff, link)){
        int x = link.first.x - xDiff;
        int y = link.first.y + yDiff;
        int x2 = link.second.x + xDiff;
        int y2 = link.second.y - yDiff;
        while((withinBounds(width, height, coor(x, y)))){
            network[y][x] = '#';
            x = x - xDiff;
            y = y + yDiff;
        }

        while(withinBounds(width, height, coor(x2, y2))){
            network[y2][x2] = '#';
            x2 = x2 + xDiff;
            y2 = y2 - yDiff;
        }
    }

}


int main() {
    std::cout << "Hello, World!" << std::endl;

    std::ifstream ifs("data.txt");
    std::string line;

    using Network = std::vector<std::string>;
    using Nodes = std::unordered_map<char, std::vector<coor>>;
    Network network;
    Nodes nodes;

    int y = 0;
    while(std::getline(ifs, line)){
            int x = 0;
            network.emplace_back(line);
            for(const auto& elem: line){
                if(elem != '.'){
                    nodes[elem].emplace_back(coor(x, y));

                }
                x++;
            }
            y++;
    }



    for(const auto& ln: network){
        std::cout << ln << "\n";
    }

    for(const auto& nodeVector: nodes){
        std::cout << nodeVector.first << " : ";
        for(const auto& elem: nodeVector.second){
            std::cout << elem.x << "," << elem.y << " ";
        }
        std::cout << "\n";
    }

    for(const auto& nodeVector : nodes){
        auto comb = generateCombinations(nodeVector.second);
        for(auto& com : comb){
            createAntiNode(com, network);
        }
    }

    int sum = 0;
    for(const auto& ln : network){
        for(const auto& chara: ln){
            if(chara != '.'){
                sum++;
            }
        }
    }

    for(const auto& ln: network){
        std::cout << ln << "\n";
    }

    std::cout << "TOTAL :" << sum << "\n";



    return 0;
}
