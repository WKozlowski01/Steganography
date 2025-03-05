# Steganografia - Ukrywanie wiadomości w obrazach BMP i PNG

## Opis

Ten program umożliwia ukrywanie oraz odczytywanie informacji w plikach graficznych w formatach BMP i PNG. Działa poprzez modyfikację pikseli obrazu w sposób niewidoczny dla ludzkiego oka.

## Wymagania

- Kompilator obsługujący standard C++ (np. g++, clang, MSVC)
- Biblioteka [fmt](https://github.com/fmtlib/fmt) (dla formatowania wyjścia)

## Kompilacja

Aby skompilować program, użyj komendy:

```sh
 g++ main.cpp -o steganografia -std=c++20 -lfmt
```

Lub z użyciem CMake (jeśli masz skonfigurowany `CMakeLists.txt`).

## Flagi programu

- `-i` / `--info` – Wyświetla informacje o pliku graficznym, takie jak jego format, rozdzielczość i inne metadane.
  - **Przykład**: `-i C:\Users\Jan\Pulpit\obraz.PNG`
- `-e` / `--encrypt` – Ukrywa podaną wiadomość w obrazie poprzez modyfikację jego pikseli.
  - **Przykład**: `-e C:\Users\Jan\Pulpit\obraz.PNG "tajna wiadomość"`
- `-d` / `--decrypt` – Odczytuje ukrytą wiadomość z obrazu.
  - **Przykład**: `-d C:\Users\Jan\Pulpit\obraz.PNG`
- `-c` / `--check` – Sprawdza, czy podana wiadomość może zostać zapisania w pliku graficznym.
  - **Przykład**: `-c C:\Users\Jan\Pulpit\obraz.PNG "tajna wiadomość"`
- `-h` / `--help` – Wyświetla pomoc i informacje na temat użycia programu.
  - **Przykład**: `-h`

## Parametry wywołania w CLion

Aby uruchomić program w CLionie z odpowiednimi parametrami:

1. Przejdź do **Edit Configurations**.
2. W sekcji **Program arguments** wpisz np.:
   - `-e C:\Users\Jan\Pulpit\obraz.PNG "tajna wiadomość"`
   - `-d C:\Users\Jan\Pulpit\obraz.PNG`
   - `-c C:\Users\Jan\Pulpit\obraz.PNG "tajna wiadomość"`
3. Zapisz zmiany i uruchom program.

## Obsługiwane formaty

- BMP (Bitmap)
- PNG (Portable Network Graphics)

## Uwagi

- Program nie obsługuje innych formatów obrazów.
- Przed uruchomieniem upewnij się, że masz prawa do edycji pliku graficznego.

## Licencja

Projekt udostępniany jest na licencji MIT. Możesz go dowolnie modyfikować i używać do własnych celów.

