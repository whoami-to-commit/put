#include <iostream>
#include <map>
#include <vector>
#include <regex>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

void fill_vector(std::vector<string>& tab)
{
    for (size_t i=0; i<tab.size(); i++) //zamiast int mozna wpisac size_t
    {
    std::cin>>tab[i];
    }
}

string href_trim(string &href_full)
{
    //trim regex ^(https?:\/\/www.)?([\da-z\.-]+[a-z\.]{2,6})([\/\w \.-]*)*\/?$

    std::regex r4(R"((https?:\/\/www.)?([\da-z\.-]+[a-z\.]{2,6})([\/\w \.-]*)*\/?)");

    std::regex r5(R"((https?:\/\/|[www.])?([\da-z\.-]+[a-z\.]{2,6})([\/\w \.-]*)*\/?)");

    std::map<std::string, std::vector<std::string>> dane;
    string linki;
    vector<string> telefony;

    std::smatch m;

    while(std::regex_search(href_full,m,r5))
    {
        std::cout<<"from regex cut: "<<m[2]<<endl;
        linki = m[2];
        //dane[m[2]].emplace_back();

        //test regex ((https?:\/\/|[www.])?([\da-z\.-]+[a-z\.]{2,6})([\/\w \.-]*)*\/?) grupa 3


     //   href_full.erase(std::remove(href_full.begin(), href_full.end(), "https"), href_full.end());
    //    href_full.erase(std::remove(href_full.begin(), href_full.end(), "http"), href_full.end());
       href_full = m.suffix();
    }
    cout<<"test"<<endl;
    for (auto& kv : dane)
    {
        std::cout << "loop: " << kv.first << " "<<endl;
    }

    return linki;

}

int main()
{

    std::map<std::string, std::vector<std::string>> dane;
    std::map<std::string, std::vector<std::string>> dane2;
    string linki,linki2;
    vector<string> telefony,telefony2;
     std::vector<std::pair<std::string,vector<string>>> to_copy;

    std::fstream file1("plik1.html", std::ios::in);
        if(file1.is_open()){
              std::stringstream str_stream;
              str_stream << file1.rdbuf(); //przepisuje zawartoĹ›Ä‡ pliku do strumienia
              std::string full_text = str_stream.str(); //zapisuje caĹ‚Ä… zawartoĹ›Ä‡ strumienia do std::string
              std::regex r(R"(([-\s]*(\d)){9})");
              std::regex pom(R"(\d+(\s|-)\d+(\s|-)\d+(\s|-)\d+)");
              std::regex r2(R"(<div class="r"><a href="([^"]+))");
              std::regex r3(R"(<div class="s"><div><span class="st">([-\s]*\d*))");
              std::regex r4(R"((https?:\/\/www.)?([\da-z\.-]+[a-z\.]{2,6})([\/\w \.-]*)*\/?)");
              cout<<"Hiperlacza: "<<endl;

              std::smatch m;
              std::smatch m2;

/*
              while (str_stream>>linki) {

                  while(std::regex_search(full_text,m,r2))
                  {
                      std::cout<<"from regex: "<<m[1]<<endl;
                      linki = m[1];
                     // dane[m[1]].emplace_back();

                     full_text = m.suffix();
                }
                     for (auto& kv : dane)
                     {
                         std::cout << "loop: " << kv.first << " "<<endl;
                     }

              }
             */
            string href_trimmed;
           // dane[linki] = telefony;
           // dane[linki] = telefony;
             while(std::regex_search(full_text,m,r2))
              {
                  std::cout<<"from regex: "<<m[1]<<endl;
                  linki = m[1];
                  dane[m[1]].emplace_back();
                href_trimmed=href_trim(linki);
               // dane[linki] = telefony;
               // dane[m[1]].emplace_back(href_trimmed);
                 full_text = m.suffix();
                 //dane[m[1]].emplace_back();

              }


       //       while(std::regex_search(full_text,m,r4))
         //    {
        //          std::cout<<"from regex: "<<m[2]<<endl;
               //   linki = m[2];
               //  dane[m[2]].emplace_back();

       //          full_text = m.suffix();
       //       }

              cout<<"test"<<endl;
              for (auto& kv : dane)
             {
                  std::cout << "loop: " << kv.first << " "<<endl;
              }

              cout<<"Numery: "<<endl;
            while(std::regex_search(full_text,m2,r))
            {
                linki2 = m2[0];
                dane2[m2[0]].emplace_back();
               // str_stream >> telefony.emplace_back();
                //assert( dane.find( linki )->second == telefony );

                cout<<"from regex: "<<m2[0]<<endl;
                full_text=m2.suffix();
            }
            cout<<"test"<<endl;
            for (auto& kv : dane2)
            {
                std::cout << "loop: " << kv.first << " "<<endl;
            }

       //     string href_trimmed=href_trim(linki);
       //     cout<<href_trimmed<<endl;

            //    for (size_t i=0; i<telefony.size(); i++){
              //  std::cout << "loop: " << telefony[i] << " "<<endl;}

         unique_copy(dane2.begin(),dane2.end(),back_inserter(to_copy));

              for(size_t i = 0; i < to_copy.size(); ++i)
                       cout <<"to copy:" <<to_copy[i].first << " : "  << endl;




            }

        std::fstream output("domeny_telefony.csv", std::ios::out | std::ios::app);
        if (output.is_open()) {
            output<<"Domena"<<","<<"Telefony"<<endl;
            for (auto& kv : dane)
           {
                output<< kv.first <<","<<endl;
                }
            for(size_t i = 0; i < to_copy.size(); ++i)
                   output<<linki<<","<<to_copy[i].first << ","<< endl;
              }
     //   }
              output.close();

}

