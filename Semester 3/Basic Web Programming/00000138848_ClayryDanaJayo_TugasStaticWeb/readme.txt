Kedai Kopi Nusantara — Website Profil Perusahaan Statis
=====================================================

Nama : Clayry Dana Jayo
NIM  : 00000138848

Struktur Berkas & Folder
------------------------
kedai-kopi-nusantara/
├── index.html          (Beranda)
├── about.html          (Tentang Kami)
├── menu.html           (Menu — grid card statis, tanpa filter)
├── gallery.html        (Galeri — 8 foto)
├── contact.html        (Info kontak, iframe peta, formulir statis)
├── readme.txt          (berkas ini)
├── css/
│   └── style.css       (palet global tema kopi + reset)
└── assets/
    └── images/         (disiapkan untuk salinan gambar lokal;
                         saat ini situs memakai URL CDN Unsplash
                         sehingga tidak ada gambar yang rusak)

Halaman & Tata Letak (Layout)
-----------------------------
- index.html   : Hero (nama + slogan + CTA ke menu.html), ikhtisar,
                 4 card fitur (col-12 / col-md-6 / col-lg-3).
- about.html   : Cerita 2 kolom (gambar di kiri, teks di kanan, col-lg-6),
                 Visi & Misi berdampingan (masing-masing col-lg-6),
                 Tim 3 kolom (masing-masing col-lg-4).
- menu.html    : 6 card statis berisi gambar, nama, deskripsi,
                 harga dalam Rupiah (col-12 / col-md-6 / col-lg-4).
- gallery.html : 8 foto beserta takarir/keterangan gambar
                 (col-6 / col-md-4 / col-lg-3).
- contact.html : Informasi + iframe peta (col-lg-6) dan formulir statis
                 berisi Nama, Email, Pesan + tombol Kirim (col-lg-6).
