## Geliştirilme Amacı

Bu proje, temel C++ programlama kavramlarını (çok boyutlu diziler, oyun mantığı simülasyonu, girdi doğrulama ve basit yapay zeka algoritmaları) pekiştirmek amacıyla bir **üniversite ders ödevi** kapsamında geliştirilmiştir.
# C++ Reversi (Othello) CLI

Standart C++ (`C++11` ve üzeri) ile geliştirilmiş, terminal üzerinden oynanabilen konsol tabanlı bir **Reversi (Othello)** oyunudur. Kullanıcı (`O`), açgözlü (greedy) hamle optimizasyonu kullanan bilgisayara (`X`) karşı mücadele eder.

## Özellikler

- **Esnek Tahta Boyutu:** Oyun başlangıcında 8x8, 10x10 veya 12x12 tahta boyutları seçilebilir.
- **Akıllı Bilgisayar Hamlesi:** Bilgisayar, her turda tahtadaki taş durumunu analiz ederek en çok taşı çeviren hamleyi seçer (Greedy AI).
- **Girdi Doğrulama:** Koordinat formatı (örneğin `4c`), sınır kontrolleri ve geçerli hamle kontrolleri dinamik olarak denetlenir.
- **Otomatik Pas ve Bitiş Kontrolü:** İki oyuncudan birinin geçerli hamlesi kalmadığında tur otomatik olarak devreder; iki tarafın da hamlesi kalmadığında oyun skor tablosu ile sonlanır.
- **Harici Kütüphane Bağımlılığı Yok:** Sadece C++ Standart Kütüphanesi (`iostream`, `string`, `cctype`) kullanılarak yazılmıştır.

## Kurulum ve Derleme

Projeyi yerel makinenize klonlayıp herhangi bir modern C++ derleyicisi (GCC, Clang, MSVC) ile derleyebilirsiniz.

### GCC / Clang ile Derleme:

```bash
g++ -std=c++11 -O2 main.cpp -o reversi
