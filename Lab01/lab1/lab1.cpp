#include <iostream>
#include <cmath>
#include <string>

using namespace std;

typedef struct City {
    string name;
    int latitude;
    int longitude;

    City() : City("\0", 0, 0) {}

    City(string name, int latitude, int longitude) :
        name(name),
        latitude(latitude),
        longitude(longitude)
    {}

    double getDistance(City city) {
        return pow((double)latitude - city.latitude, 2) + pow((double)longitude - city.longitude, 2);
    }

    bool operator==(const City& rhs) {
        return name == rhs.name && latitude == rhs.latitude && longitude == rhs.longitude;
    }
};

typedef struct Node {
    City city;
    Node* next;

    Node() : Node(City()) {}
    Node(City city) : city(city), next(nullptr) {}
};

typedef struct List {
    Node* head;

    List() {
        head = new Node();
    }

    ~List() {
        Node* temp = head;
        while (head != nullptr) {
            temp = temp->next;
            delete head;
            head = temp;
        }
    }

    void travel() {
        Node* node = head->next;
        while (node != nullptr) {
            cout << node->city.name << " ";
            node = node->next;
        }
        cout << endl;
    }

    void insert(City city) {
        Node* node = new Node(city);
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = node;
    }

    Node* find(City city) {
        Node* temp = head->next;
        while (temp != nullptr) {
            temp = temp->next;
            if (temp->city == city) {
                return temp;
            }
        }
        return nullptr;
    }

    Node* find(string name) {
        Node* temp = head->next;
        while (temp != nullptr) {
            if (temp->city.name == name) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    void remove(City city) {
        Node* pre = head;
        Node* cur = head->next;
        while (cur != nullptr && !(cur->city == city)) {
            pre = cur;
            cur = cur->next;
        }
        if (cur) {
            pre->next = cur->next;
            delete cur;
        }
    }

    void findCitiesWithinDistance(double latitude, double longitude, double distance, List& list) {
        
        Node* cur = head->next;
        while (cur != nullptr) {
            if (cur->city.getDistance(City("\0", latitude, longitude)) <= distance) {
                list.insert(cur->city);
            }
            cur = cur->next;
        }
    }
};

int main()
{
    List list;
    int cityCnt, longitude, latitude;
    cout << "输入城市数\n";
    string name;
    cin >> cityCnt;
    while (cityCnt) {
        cout << "输入纬度 经度 城市名\n";
        cin >> latitude >> longitude >> name;
        list.insert(City(name, latitude, longitude));
        --cityCnt;
    }
    cout << "输入要查询的城市名\n";
    cin >> name;
    Node* node = list.find(name);
    if (node == nullptr) {
       cout << "没有这个城市\n";
    } else {
       cout << "经度: " << node->city.longitude << " 纬度: " << node->city.latitude << endl;
    }
    cout << "输入经度 纬度 距离\n";
    int distance;
    cin >> longitude >> latitude >> distance;
    List list2;
    list.findCitiesWithinDistance(latitude, longitude, distance, list2);
    list2.travel();
    return 0;
}