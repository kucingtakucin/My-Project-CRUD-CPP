#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "crud.h"

void crud::writeData(std::fstream &data,int posisi,crud::Mahasiswa &inputMahasiswa){
    data.seekp((posisi - 1) * sizeof(crud::Mahasiswa),std::ios::beg);
    data.write(reinterpret_cast<char*>(&inputMahasiswa),sizeof(crud::Mahasiswa));
}

crud::Mahasiswa crud::readData(std::fstream &data,int posisi){
    crud::Mahasiswa readMahasiswa;
    data.seekg((posisi - 1) * sizeof(Mahasiswa),std::ios::beg);
    data.read(reinterpret_cast<char*>(&readMahasiswa),sizeof(crud::Mahasiswa));
    return readMahasiswa;
}

int crud::getDataSize(std::fstream &data){
    int start,end;
    
    data.seekg(0,std::ios::beg);
    start = data.tellg();
    data.seekg(0,std::ios::end);
    end = data.tellg();
    return (end - start) / sizeof(crud::Mahasiswa);
}

void crud::listMahasiswa(std::fstream &data){
    int size = crud::getDataSize(data);
    crud::Mahasiswa showMahasiswa;
    std::cout << "No \t Pk \t NIM \t Nama \t Jurusan" << std::endl;
    for (int i = 1; i <= size; i++){
        showMahasiswa = crud::readData(data,i);
        std::cout << i << std::endl;
        std::cout << showMahasiswa.pk << std::endl;
        std::cout << showMahasiswa.NIM << std::endl;
        std::cout << showMahasiswa.nama << std::endl;
        std::cout << showMahasiswa.jurusan << std::endl;
    }
}

void crud::deleteMahasiswa(std::fstream &data){
    int nomor,size,offset;
    crud::Mahasiswa blankMahasiswa,tempMahasiswa;
    std::fstream dataSementara;

    size = crud::getDataSize(data);
    // 1. Pilih nomor
    listMahasiswa(data);
    std::cout << "Pilih nomor yang akan kamu hapus : " << std::endl;
    std::cin >> nomor;

    // 2. Di posisi ini kita isi dengan data kosong
    crud::writeData(data,nomor,blankMahasiswa);

    /* 3. Kita cek data yand ada dari file data.bin, kalau ada data nya, kita pindahkan ke file sementara */
    dataSementara.open("temp.dat",std::ios::trunc | std::ios::out | std::ios::in | std::ios::binary);

    offset = 0;
    for (int i = 1; i <= size; i++){
        tempMahasiswa = crud::readData(data,i);
        if (!tempMahasiswa.nama.empty()){
            crud::writeData(dataSementara,i - offset,tempMahasiswa);
        } else {
            offset++;
            std::cout << "Data sudah terhapus!" << std::endl;
        }
    }
    
    // 4. Kita pindahkan data dari file sementara ke data.bin
    size = crud::getDataSize(dataSementara);
    data.close();
    data.open("Mahasiswa.bin",std::ios::trunc | std::ios::out | std::ios::binary);
    data.close();
    data.open("Mahasiswa.bin",std::ios::out | std::ios::in | std::ios::binary);

    for (int i = 1; i <= size; i++){
        tempMahasiswa = crud::readData(dataSementara,i);
        crud::writeData(data,i,tempMahasiswa);
    }
}

void crud::updateMahasiswa(std::fstream &data){
    int nomor;
    crud::Mahasiswa updateMahasiswa;
    std::cout << "Pilih nomor yang akan kamu update : ";
    std::cin >> nomor;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    updateMahasiswa = crud::readData(data,nomor);
    std::cout << "\nData yang akan kamu update : " << std::endl;
    std::cout << "NIM      : " << updateMahasiswa.NIM << std::endl;
    std::cout << "Nama     : " << updateMahasiswa.nama << std::endl;
    std::cout << "Jurusan  : " << updateMahasiswa.jurusan << std::endl;
    std::cout << std::endl;

    std::cout << "NIM      : " << std::endl;
    std::getline(std::cin,updateMahasiswa.NIM);
    std::cout << "Nama     : " << std::endl;
    std::getline(std::cin,updateMahasiswa.nama);
    std::cout << "Jurusan  : " << std::endl;
    std::getline(std::cin,updateMahasiswa.jurusan);

    crud::writeData(data,nomor,updateMahasiswa);
}

void crud::cekDatabase(std::fstream &data){
    data.open("Mahasiswa.bin",std::ios::out | std::ios::in | std::ios::binary);

    if (data.is_open()){
        std::cout << "Database ditemukan!" << std::endl;
    } else {
        std::cout << "Database tidak ditemukan!" << std::endl;
        std::cout << "Silahkan tambah Mahasiswa terlebih dahulu!" << std::endl;
        data.close();
        data.open("Mahasiswa.bin",std::ios::trunc | std::ios::out | std::ios::in | std::ios::binary);
    }
}

void crud::tambahMahasiswa(std::fstream &data){
    crud::Mahasiswa inputMahasiswa,lastMahasiswa;
    int size = crud::getDataSize(data);
    std::cout << "Ukuran data : " << size << std::endl;

    if (size == 0){
        inputMahasiswa.pk = 1;
    } else {
        lastMahasiswa = crud::readData(data,size);
        std::cout << "pk = " << lastMahasiswa.pk << std::endl;
        inputMahasiswa.pk = lastMahasiswa.pk + 1;
    }
    
    std::cout << "NIM     : ";
    std::getline(std::cin,inputMahasiswa.NIM);
    std::cout << "Nama    : ";
    std::getline(std::cin,inputMahasiswa.nama);
    std::cout << "Jurusan : ";
    std::getline(std::cin,inputMahasiswa.jurusan);

    crud::writeData(data,size + 1,inputMahasiswa);
}

int crud::MainMenu(){
    int inputUser;
    std::system("clear");

    std::cout << "====== DATABASE SIAKAD UNIVERSITAS NEGERI WAKANDA ======\n" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "1. List Seluruh Data Mahasiswa" << std::endl;
    std::cout << "2. Search Data Mahasiswa" << std::endl;
    std::cout << "3. Tambah Data Mahasiswa" << std::endl;
    std::cout << "4. Update Data Mahasiswa" << std::endl;
    std::cout << "5. Delete Data Mahasiswa" << std::endl;
    std::cout << "6. Selesai" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "\nPilihan kamu : ";
    std::cin >> inputUser;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    
    return inputUser;
}