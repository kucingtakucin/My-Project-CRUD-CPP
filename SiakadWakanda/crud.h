#include <fstream>
#include <string>

namespace crud{
    struct Mahasiswa{
        int pk;
        std::string NIM;
        std::string nama;
        std::string jurusan;
    }; 

int MainMenu();
void cekDatabase(std::fstream &data);
void writeData(std::fstream &data,int posisi,Mahasiswa &inputMahasiswa);
int getDataSize(std::fstream &Mahasiswa);
Mahasiswa readData(std::fstream &data,int posisi);
void tambahMahasiswa(std::fstream &data);
void listMahasiswa(std::fstream &data);
void updateMahasiswa(std::fstream &data);
void deleteMahasiswa(std::fstream &data);
} // namespace crud
