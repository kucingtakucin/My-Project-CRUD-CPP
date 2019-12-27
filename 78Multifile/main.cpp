#include <iostream>
#include <fstream>
#include <string>
#include "crud.h"

int main(int argc, char const *argv[]){
    std::fstream data;
    crud::cekDatabase(data);
    int pilihan = crud::MainMenu();
    char is_continue;
    enum option{READ = 1,SEARCH,CREATE,UPDATE,DELETE,FINISH};

        while (pilihan != FINISH){
        switch (pilihan){
            case READ:
                std::cout << "\n                              =================================" << std::endl;
                std::cout << "                              ====== LIST DATA MAHASISWA ======" << std::endl;
                std::cout << "                              =================================" << std::endl;
                crud::listMahasiswa(data);
                break;
            case SEARCH:
                std::cout << "\n                              =================================" << std::endl;
                std::cout << "                              ====== SEARCH DATA MAHASISWA ======" << std::endl;
                std::cout << "                              =================================" << std::endl;
                break;
            case CREATE:
                std::cout << "\n                              =================================" << std::endl;
                std::cout << "                              ====== TAMBAH DATA MAHASISWA ======" << std::endl;
                std::cout << "                              =================================" << std::endl;
                crud::tambahMahasiswa(data);
                break;
            case UPDATE:
                std::cout << "\n                              =================================" << std::endl;
                std::cout << "                              ====== UPDATE DATA MAHASISWA ======" << std::endl;
                std::cout << "                              =================================" << std::endl;
                crud::updateMahasiswa(data);
                break;
            case DELETE:
                std::cout << "\n                              =================================" << std::endl;
                std::cout << "                              ====== DELETE DATA MAHASISWA ======" << std::endl;
                std::cout << "                              =================================" << std::endl;
                crud::deleteMahasiswa(data);
                break;
            default:
                std::cout << "Pilihan kamu tidak ditemukan!" << std::endl;
        }
        label_continue:
        std::cout << "Apakah kamu ingin melanjutkan? (Y/N) ";
        std::cin >> is_continue;

        if ((is_continue == 'Y' || (is_continue == 'y'))){
            pilihan = crud::MainMenu();
        } else if (is_continue == 'N' || is_continue == 'n'){
            break;
        } else {
            goto label_continue;
        }
    }
    
    std::cout << "Akhir dari program" << std::endl;

    std::cin.get();
    return 0;
}
