#include <iostream>
#include <vector>
#include <string>

using namespace std;


struct Archivo {
    string name;
};

struct Directorio {
    string name;
    vector<Archivo> archivos;
    vector<Directorio> subdirectorio;
};

bool findfile(Directorio& dir, string& path, string& target){
    // Caso base
    for(auto arch: dir.archivos) {
        if(arch.name == target) {
            path += "/" + dir.name;
            return true;
        }
    }
    
    for(auto& subdir: dir.subdirectorio) {
        string subdirpath = path + "/" + dir.name;
        if(findfile(subdir, subdirpath, target)){
            path = subdirpath;
            return true;
        }
    }

    return false;
};

int main()
{
    Directorio sistemaDeArchivos = {
        "root",
        {
                {"archivo1.txt"},
                {"archivo2.txt"}
        },
        {
                {
                    "subdir1",
                    {
                        {"archivo3.txt"},
                    },
                    {
                        {
                            "subdir2",
                            {
                                {"target.txt"},
                                {"archivo4.txt"}
                            },
                            {}
                        }
                    }
                },
                {"archivo5.txt"}
        }
    };
    string target = "2.txt";
    string path = "";

    cout << &sistemaDeArchivos << endl;

    if(findfile(sistemaDeArchivos, path, target)){
        cout << "Archivo encontrado en: " << path << "/" << target;
    } else {
        cout << "Arhivo no encontrado :c" << endl;
    }
        

    return 0;
}