CREATE DATABASE IF NOT EXISTS praktikum_week2;
USE praktikum_week2;

-- SOAL 1

CREATE TABLE Calon (
    ID_Calon VARCHAR(10) PRIMARY KEY,
    Nama_Calon VARCHAR(100) NOT NULL
);

CREATE TABLE Pemilih (
    ID_Pemilih VARCHAR(10) PRIMARY KEY,
    Nama_Pemilih VARCHAR(100) NOT NULL,
    Nomor_Telepon_Penduduk VARCHAR(20)
);

CREATE TABLE Pemilihan (
    ID_Calon VARCHAR(10),
    ID_Pemilih VARCHAR(10),
    PRIMARY KEY (ID_Calon, ID_Pemilih),
    FOREIGN KEY (ID_Calon) REFERENCES Calon(ID_Calon) ON DELETE CASCADE,
    FOREIGN KEY (ID_Pemilih) REFERENCES Pemilih(ID_Pemilih) ON DELETE CASCADE
);

INSERT INTO Calon (ID_Calon, Nama_Calon) VALUES
('PR001', 'Dennis Wicaksana'),
('PR002', 'Arya Gunawan');

INSERT INTO Pemilih (ID_Pemilih, Nama_Pemilih, Nomor_Telepon_Penduduk) VALUES
('PD001', 'Anna', '2031203'),
('PD002', 'Sukijah', '2301223'),
('PD003', 'Kana', '2334059'),
('PD004', 'Kiri', '2033012'),
('PD005', 'Okta', '9332333');

INSERT INTO Pemilihan (ID_Calon, ID_Pemilih) VALUES
('PR001', 'PD001'),
('PR001', 'PD002'),
('PR001', 'PD004'),
('PR002', 'PD003'),
('PR002', 'PD005');

-- SOAL 2

CREATE TABLE Orders (
    IDOrder VARCHAR(10) PRIMARY KEY,
    Nomor_Meja INT NOT NULL,
    JamMasuk TIME NOT NULL,
    JamKeluar TIME NOT NULL
);

CREATE TABLE Menu (
    IDMenu VARCHAR(10) PRIMARY KEY,
    NamaMenu VARCHAR(100) NOT NULL,
    Kategori VARCHAR(50) NOT NULL,
    Harga INT NOT NULL
);

CREATE TABLE OrderDetail (
    IDOrder VARCHAR(10),
    IDMenu VARCHAR(10),
    PRIMARY KEY (IDOrder, IDMenu),
    FOREIGN KEY (IDOrder) REFERENCES Orders(IDOrder) ON DELETE CASCADE,
    FOREIGN KEY (IDMenu) REFERENCES Menu(IDMenu) ON DELETE CASCADE
);

INSERT INTO Orders (IDOrder, Nomor_Meja, JamMasuk, JamKeluar) VALUES
('OD001', 1, '10:00:00', '11:00:00'),
('OD002', 2, '11:00:00', '13:00:00'),
('OD003', 1, '15:00:00', '15:30:00'),
('OD004', 1, '15:00:00', '15:30:00');

INSERT INTO Menu (IDMenu, NamaMenu, Kategori, Harga) VALUES
('MN001', 'Nasi Putih', 'Makanan Pokok', 5000),
('MN002', 'Tahu Goreng', 'Lauk', 4000),
('MN003', 'Air Mineral', 'Minuman', 3000),
('MN004', 'Ayam Goreng', 'Lauk', 15000);

INSERT INTO OrderDetail (IDOrder, IDMenu) VALUES
('OD001', 'MN001'),
('OD001', 'MN002'),
('OD001', 'MN003'),
('OD002', 'MN001'),
('OD002', 'MN004'),
('OD003', 'MN002'),
('OD004', 'MN004');