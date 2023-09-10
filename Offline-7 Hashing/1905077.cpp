#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;
char *random(int T)
{
    char *word = new char[7];
    int r;
    srand(T);
    for (int i = 0; i < 7; i++)
    {
        r = rand() % 26;
        word[i] = char('a' + r);
    }
    return word;
}

int hashFunction1(string s, int num)
{
    long long int h = 0;
    int a = 37;
    h = s[0];
    for (int i = 1; i < s.length(); i++)
    {
        h = s[i] + a * h;
    }
    return h % num;
}

int hashFunction2(string str, int num)
{
    int primaryNumber = 29;
    int hashValue = 0;
    for (int i = 0; i < str.length(); i++)
    {
        hashValue = primaryNumber * hashValue + str.at(i);
    }

    int index = 44497 - (hashValue % 44497);

    return index;
}

class HashTable1
{
    list<pair<string, int>> *ll;
    int total;
    int num;

public:
    HashTable1(int num)
    {
        this->num = num;
        total = 0;
        ll = new list<pair<string, int>>[num];
    }
    void insert1(pair<string, int> p)
    {
        int check = 1;

        int index = hashFunction1(p.first, num);

        for (pair<string, int> pp : ll[index])
        {
            if (pp.first == p.first)
            {
                check = 0;
                // cout<<"This already exists"<<endl;
            }
        }
        if (check)
        {
            // total++;
            ll[index].push_back(p);
        }
    }

    void delete1(string s)
    {

        int pos = hashFunction1(s, num);
        pair<string, int> p;
        int flag;
        list<pair<string, int>>::iterator it;
        for (it = ll[pos].begin(); it != ll[pos].end(); it++)
        {

            if ((*it).first == s)
            {

                p = *it;
                flag = 1;
                break;
            }

            else
                flag = 0;
        }

        if (flag)
            ll[pos].remove(p);

        // else
        // cout<<"Not found"<<endl;
    }
    void search1(string s)
    {
        int check = 1;

        int index = hashFunction1(s, num);
        for (pair<string, int> pp : ll[index])
        {
            if (pp.first == s)
            {
                // cout<<"This already exists"<<endl;
                // cout<<pp.first<<endl;
                check = 0;
            }
        }
        if (check == 1)
        { // cout<<"this string doesn't exists";}
        }
    }
};

class HashTable2
{
    pair<string, int> *ll;
    int total;
    int num;

public:
    HashTable2(int num)
    {
        this->num = num;
        ll = new pair<string, int>[num];
        for (int i = 0; i < num; i++)
        {
            pair<string, int> p("", -1);
            ll[i] = p;
        }
    }
    void insert2(pair<string, int> p)
    {
        int check = 1;
        int probe = 0;
        for (int i = 0; i < num; i++)
        {
            if (ll[i].first == p.first)
            {
                // cout<<"This string already exists"<<endl;
                return;
            }
        }

        int index = hashFunction1(p.first, num);
        while (ll[index].first != "" && index != num)
        {
            index = (index + 1) % num;
            probe++;
        }
        ll[index] = p;
    }

    void delete2(string s)
    {

        int index = hashFunction1(s, num);
        while (ll[index].first != "")
        {

            if (ll[index].first == s)
            {
                // cout<<"String found at key "<<index<<endl;
                ll[index] = {"", -1};
                return;
            }

            index++;
            index %= num;
        }
        // cout<<"Not found"<<endl;
    }
    int search2(string s)
    {
        int index = hashFunction1(s, num);
        int probe = 0, check = 0;
        while (ll[index].first != "")
        {

            if (ll[index].first == s)
            {
                // cout<<"String found at key "<<index<<endl;
                // ll[index]={"",-1};
                check = 1;
                break;
            }

            index++;
            index %= num;
            probe++;
        }
        if (check == 0)
        {
            // cout<<"Not found"<<endl;
        }
        return probe;
    }
};

class HashTable3
{
    pair<string, int> *ll;
    int total;
    int num;

public:
    HashTable3(int num)
    {
        this->num = num;
        ll = new pair<string, int>[num];
        for (int i = 0; i < num; i++)
        {
            pair<string, int> p("", -1);
            ll[i] = p;
        }
    }
    void insert3(pair<string, int> p)
    {
        int check = 1;
        int probe = 0;
        for (int i = 0; i < num; i++)
        {
            if (ll[i].first == p.first)
            {
                // cout<<"This string already exists"<<endl;
                return;
            }
        }
        int i = 1;

        int index = hashFunction1(p.first, num);
        while (ll[index].first != "" && index != num)
        {
            index = (index + i * i) % num;
            probe++;
            i++;
        }
        ll[index] = p;
    }

    void delete3(string s)
    {
        int index = hashFunction1(s, num);
        int step = 1;
        while (ll[index].first != "")
        {

            if (ll[index].first == s)
            {
                // cout<<"String found at key "<<index<<endl;
                ll[index] = {"", -1};
                return;
            }

            index = (index + step * step);
            index %= num;
        }
        // cout<<"Not found"<<endl;
    }
    int search3(string s)
    {
        int index = hashFunction1(s, num);
        int step = 1, probe = 0, check = 0;
        while (ll[index].first != "")
        {

            if (ll[index].first == s)
            {
                // cout<<"String found at key "<<index<<endl;
                check = 1;
                break;
                // return;
            }

            index = (index + step * step);
            index %= num;
            probe++;
        }
        return probe;
        // cout<<"Not found"<<endl;
    }
};

class HashTable4
{
    pair<string, int> *ll;
    int total;
    int num;

public:
    HashTable4(int num)
    {
        this->num = num;
        ll = new pair<string, int>[num];
        for (int i = 0; i < num; i++)
        {
            pair<string, int> p("", -1);
            ll[i] = p;
        }
    }
    void insert4(pair<string, int> p)
    {
        int check = 1;
        for (int i = 0; i < num; i++)
        {
            if (ll[i].first == p.first)
            {
                // cout<<"This string already exists"<<endl;
                return;
            }
        }
        int probe = 0;

        int index = hashFunction1(p.first, num);
        int step = hashFunction2(p.first, num);

        while (ll[index].first != "")
        {
            index += step;
            index %= num;
            probe++;
        }
        ll[index] = p;
    }

    void delete4(string s)
    {
        int index = hashFunction1(s, num);
        int step = hashFunction2(s, num);
        while (ll[index].first != "")
        {

            if (ll[index].first == s)
            {
                // cout<<"String found at key "<<index<<endl;
                ll[index] = {"", -1};
                return;
            }

            index += step;
            index %= num;
        }
        //	cout<<"Not found"<<endl;
    }
    int search4(string s)
    {
        int index = hashFunction1(s, num);
        int step = hashFunction2(s, num);
        int probe = 0;
        while (ll[index].first != "")
        {

            if (ll[index].first == s)
            {
                // cout<<"String found at key "<<index<<endl;
                //  ll[index]={"",-1};
                break;
            }

            index += step;
            index %= num;
            probe++;
        }
        // cout<<"Not found"<<endl;
        return probe;
    }
};

int main()
{
    int N;
    cin >> N;
    freopen("output.csv", "w", stdout);
    vector<string> words;
    vector<string> search_words;
    vector<string> del_words;
    vector<double> results;

    HashTable4 h4(N);

    HashTable1 h1(N);

    HashTable2 h2(N);

    HashTable3 h3(N);
    float load = 0.4;
    cout << "                  Table:1  Separate Chaining    " << endl;
    cout << "    ,Before Deletion,,     After Deletion" << endl;
    cout << "           ,AVG_Search_Time,      AVG_search_Time," << endl;
    for (float i = 0.4; i < 1; i += 0.1)
    {
        int sz = load * N;
        for (int i = 0; i < sz; i++)
        {
            string s1 = random(i);
            words.push_back(s1);
        }

        int a = sz / 10, b = sz / 20, p;

        for (int i = 0; i < a; i++)
        {
            p = (10 * i) + (rand() % 10);
            search_words.push_back(words[p]);
        }

        for (int i = 0; i < b; i++)
        {
            p = (2 * i) + (rand() % 2);
            del_words.push_back(search_words[p]);
        }

        int v = 1;
        float probe = 0;

        for (int i = 0; i < words.size(); i++)
        {
            h1.insert1({words[i], v++});
        }
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < a; i++)
        {
            h1.search1(search_words[i]);
        }
        auto endt = chrono::steady_clock::now();
        cout << "," << chrono::duration_cast<chrono::nanoseconds>(endt - start).count() << ",";
        results.push_back(chrono::duration_cast<chrono::nanoseconds>(endt - start).count());
        probe = 0;
        for (int i = 0; i < b; i++)
        {
            h1.delete1(del_words[i]);
        }

        start = chrono::steady_clock::now();
        for (int i = 0; i < a; i++)
        {
            h1.search1(search_words[i]);
        }
        endt = chrono::steady_clock::now();
        cout << "," << chrono::duration_cast<chrono::nanoseconds>(endt - start).count() << endl;
        results.push_back(chrono::duration_cast<chrono::nanoseconds>(endt - start).count());
        load += 0.1;
    }

    cout << endl;
    words.clear();
    search_words.clear();
    del_words.clear();

    load = 0.4;
    cout << "                  Table:2  Linear Probing    " << endl;
    cout << ",    Before Deletion,,     After Deletion" << endl;
    cout << "Load_Factor,AVG_Time,Num_OF_Probes,AVG_Time,Num_OF_Probes" << endl;
    for (float i = 0.4; i < 1; i += 0.1)
    {

        int sz = load * N;
        for (int i = 0; i < sz; i++)
        {
            string s1 = random(i);
            words.push_back(s1);
        }

        int a = sz / 10, b = sz / 20, p;

        for (int i = 0; i < a; i++)
        {
            p = (10 * i) + (rand() % 10);
            search_words.push_back(words[p]);
        }

        for (int i = 0; i < b; i++)
        {
            p = (2 * i) + (rand() % 2);
            del_words.push_back(search_words[p]);
        }

        int v = 1;
        float probe = 0;

        for (int i = 0; i < words.size(); i++)
        {
            h2.insert2({words[i], v++});
        }
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < a; i++)
        {
            probe += h2.search2(search_words[i]);
        }
        auto endt = chrono::steady_clock::now();
        cout << load << "," << chrono::duration_cast<chrono::nanoseconds>(endt - start).count() << "," << float(probe) / a << ",";
        results.push_back(chrono::duration_cast<chrono::nanoseconds>(endt - start).count());
        results.push_back(float(probe) / a);
        probe = 0;
        for (int i = 0; i < b; i++)
        {
            h2.delete2(del_words[i]);
        }

        start = chrono::steady_clock::now();
        for (int i = 0; i < a; i++)
        {
            probe += h2.search2(search_words[i]);
        }
        endt = chrono::steady_clock::now();
        cout << chrono::duration_cast<chrono::nanoseconds>(endt - start).count() << "," << float(probe) / b << endl;
        results.push_back(chrono::duration_cast<chrono::nanoseconds>(endt - start).count());
        results.push_back(float(probe) / a);
        load += 0.1;
    }

    cout << endl;
    words.clear();
    search_words.clear();
    del_words.clear();

    load = 0.4;
    cout << "                  Table:3  Quadratic Probing    " << endl;
    cout << ",    Before Deletion,,     After Deletion" << endl;
    cout << "Load_Factor,AVG_Time,Num_OF_Probes,AVG_Time,Num_OF_Probes" << endl;
    for (float i = 0.4; i < 1; i += 0.1)
    {
        int sz = load * N;
        for (int i = 0; i < sz; i++)
        {
            string s1 = random(i);
            words.push_back(s1);
        }

        int a = sz / 10, b = sz / 20, p;

        for (int i = 0; i < a; i++)
        {
            p = (10 * i) + (rand() % 10);
            search_words.push_back(words[p]);
        }

        for (int i = 0; i < b; i++)
        {
            p = (2 * i) + (rand() % 2);
            del_words.push_back(search_words[p]);
        }

        int v = 1;
        float probe = 0;

        for (int i = 0; i < words.size(); i++)
        {
            h3.insert3({words[i], v++});
        }
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < a; i++)
        {
            probe += h3.search3(search_words[i]);
        }
        auto endt = chrono::steady_clock::now();
        cout << load << "," << chrono::duration_cast<chrono::nanoseconds>(endt - start).count() << "," << float(probe) / a << ",";
        results.push_back(chrono::duration_cast<chrono::nanoseconds>(endt - start).count());
        results.push_back(float(probe) / a);
        probe = 0;
        for (int i = 0; i < b; i++)
        {
            h3.delete3(del_words[i]);
        }

        start = chrono::steady_clock::now();
        for (int i = 0; i < a; i++)
        {
            probe += h3.search3(search_words[i]);
        }
        endt = chrono::steady_clock::now();
        cout << chrono::duration_cast<chrono::nanoseconds>(endt - start).count() << "," << float(probe) / b << endl;
        results.push_back(chrono::duration_cast<chrono::nanoseconds>(endt - start).count());
        results.push_back(float(probe) / a);
        load += 0.1;
    }

    cout << endl;
    words.clear();
    search_words.clear();
    del_words.clear();

    load = 0.4;
    cout << "                  Table:4  Double hashing    " << endl;
    cout << ",    Before Deletion,,     After Deletion" << endl;
    cout << "Load_Factor,AVG_Time,Num_OF_Probes,AVG_Time,Num_OF_Probes" << endl;
    for (float i = 0.4; i < 1; i += 0.1)
    {
        int sz = load * N;
        for (int i = 0; i < sz; i++)
        {
            string s1 = random(i);
            words.push_back(s1);
        }

        int a = sz / 10, b = sz / 20, p;

        for (int i = 0; i < a; i++)
        {
            p = (10 * i) + (rand() % 10);
            search_words.push_back(words[p]);
        }

        for (int i = 0; i < b; i++)
        {
            p = (2 * i) + (rand() % 2);
            del_words.push_back(search_words[p]);
        }

        int v = 1;
        float probe = 0;

        for (int i = 0; i < words.size(); i++)
        {
            h4.insert4({words[i], v++});
        }
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < a; i++)
        {
            probe += h4.search4(search_words[i]);
        }
        auto endt = chrono::steady_clock::now();
        cout << load << "," << chrono::duration_cast<chrono::nanoseconds>(endt - start).count() << "," << float(probe) / a << ",";
        results.push_back(chrono::duration_cast<chrono::nanoseconds>(endt - start).count());
        results.push_back(float(probe) / a);
        probe = 0;
        for (int i = 0; i < b; i++)
        {
            h4.delete4(del_words[i]);
        }

        start = chrono::steady_clock::now();
        for (int i = 0; i < a; i++)
        {
            probe += h4.search4(search_words[i]);
        }
        endt = chrono::steady_clock::now();
        cout << chrono::duration_cast<chrono::nanoseconds>(endt - start).count() << "," << float(probe) / b << endl;
        results.push_back(chrono::duration_cast<chrono::nanoseconds>(endt - start).count());
        results.push_back(float(probe) / a);
        load += 0.1;
    }

    cout << endl;
    words.clear();
    search_words.clear();
    del_words.clear();

    cout << "  Table:5 Performance of various collision resolution methods in load factor 0.4   " << endl;
    cout << ",    Before Deletion,,    After Deletion" << endl;
    cout << "Method,Avg Search Time, Avg no of probes,Avg Search Time, Avg no of probes" << endl;
    cout << "Separate chaining"
         << "," << results[0] << ","
         << "N/A"
         << "," << results[1] << ","
         << "N/A" << endl;
    cout << "Linear probing"
         << "," << results[12] << "," << results[13] << "," << results[14] << "," << results[15] << endl;
    cout << "Quadratic probing"
         << "," << results[36] << "," << results[37] << "," << results[38] << "," << results[39] << endl;
    cout << "Double hashing"
         << "," << results[60] << "," << results[61] << "," << results[62] << "," << results[63] << endl;

    cout << "  Table:6 Performance of various collision resolution methods in load factor 0.5   " << endl;
    cout << ",    Before Deletion,,    After Deletion" << endl;
    cout << "Method,Avg Search Time, Avg no of probes,Avg Search Time, Avg no of probes" << endl;
    cout << "Separate chaining"
         << "," << results[2] << ","
         << "N/A"
         << "," << results[3] << ","
         << "N/A" << endl;
    cout << "Linear probing"
         << "," << results[16] << "," << results[17] << "," << results[18] << "," << results[15 + 4] << endl;
    cout << "Quadratic probing"
         << "," << results[36 + 4] << "," << results[37 + 4] << "," << results[38 + 4] << "," << results[39 + 4] << endl;
    cout << "Double hashing"
         << "," << results[60 + 4] << "," << results[61 + 4] << "," << results[62 + 4] << "," << results[63 + 4] << endl;

    cout << "  Table:5 Performance of various collision resolution methods in load factor 0.6   " << endl;
    cout << ",    Before Deletion,,    After Deletion" << endl;
    cout << "Method,Avg Search Time, Avg no of probes,Avg Search Time, Avg no of probes" << endl;
    cout << "Separate chaining"
         << "," << results[4] << ","
         << "N/A"
         << "," << results[5] << ","
         << "N/A" << endl;
    cout << "Linear probing"
         << "," << results[12 + 8] << "," << results[13 + 8] << "," << results[14 + 8] << "," << results[15 + 8] << endl;
    cout << "Quadratic probing"
         << "," << results[36 + 8] << "," << results[37 + 8] << "," << results[38 + 8] << "," << results[39 + 8] << endl;
    cout << "Double hashing"
         << "," << results[60 + 8] << "," << results[61 + 8] << "," << results[62 + 8] << "," << results[63 + 8] << endl;

    cout << "  Table:5 Performance of various collision resolution methods in load factor 0.7   " << endl;
    cout << ",    Before Deletion,,    After Deletion" << endl;
    cout << "Method,Avg Search Time, Avg no of probes,Avg Search Time, Avg no of probes" << endl;
    cout << "Separate chaining"
         << "," << results[6] << ","
         << "N/A"
         << "," << results[7] << ","
         << "N/A" << endl;
    cout << "Linear probing"
         << "," << results[12 + 12] << "," << results[13 + 12] << "," << results[14 + 12] << "," << results[15 + 12] << endl;
    cout << "Quadratic probing"
         << "," << results[36 + 12] << "," << results[37 + 12] << "," << results[38 + 12] << "," << results[39 + 12] << endl;
    cout << "Double hashing"
         << "," << results[60 + 12] << "," << results[61 + 12] << "," << results[62 + 12] << "," << results[63 + 12] << endl;

    cout << "  Table:5 Performance of various collision resolution methods in load factor 0.8   " << endl;
    cout << ",    Before Deletion,,    After Deletion" << endl;
    cout << "Method,Avg Search Time, Avg no of probes,Avg Search Time, Avg no of probes" << endl;
    cout << "Separate chaining"
         << "," << results[8] << ","
         << "N/A"
         << "," << results[9] << ","
         << "N/A" << endl;
    cout << "Linear probing"
         << "," << results[12 + 16] << "," << results[13 + 16] << "," << results[14 + 16] << "," << results[15 + 16] << endl;
    cout << "Quadratic probing"
         << "," << results[36 + 16] << "," << results[37 + 16] << "," << results[38 + 16] << "," << results[39 + 16] << endl;
    cout << "Double hashing"
         << "," << results[60 + 16] << "," << results[61 + 16] << "," << results[62 + 16] << "," << results[63 + 16] << endl;

    cout << "  Table:5 Performance of various collision resolution methods in load factor 0.9   " << endl;
    cout << ",    Before Deletion,,    After Deletion" << endl;
    cout << "Method,Avg Search Time, Avg no of probes,Avg Search Time, Avg no of probes" << endl;
    cout << "Separate chaining"
         << "," << results[10] << ","
         << "N/A"
         << "," << results[11] << ","
         << "N/A" << endl;
    cout << "Linear probing"
         << "," << results[12 + 20] << "," << results[13 + 20] << "," << results[14 + 20] << "," << results[15 + 20] << endl;
    cout << "Quadratic probing"
         << "," << results[36 + 20] << "," << results[37 + 20] << "," << results[38 + 20] << "," << results[39 + 20] << endl;
    cout << "Double hashing"
         << "," << results[60 + 20] << "," << results[61 + 20] << "," << results[62 + 20] << "," << results[63 + 20] << endl;

    return 0;
}
