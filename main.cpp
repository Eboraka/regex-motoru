#include <iostream>
#include <string>
using namespace std;

// desen[d...] ile metin[m...] eşleşiyor mu?
bool esles(const string& desen, size_t d, const string& metin, size_t m)
{
    // Desen bittiyse metin de bitmiş olmalı
    if (d == desen.size())
        return m == metin.size();

    // Bu harften sonra * + ? var mı?
    char sonraki = (d + 1 < desen.size()) ? desen[d + 1] : '\0';

    // Şu anki desen harfi metindeki harfe uyuyor mu? ('.' her harfe uyar)
    bool uyuyor = (m < metin.size()) && (desen[d] == '.' || desen[d] == metin[m]);

    if (sonraki == '*')  // 0 kez: harfi atla | 1+ kez: harfi tüket, aynı yerde kal
        return esles(desen, d + 2, metin, m) || (uyuyor && esles(desen, d, metin, m + 1));

    if (sonraki == '+')  // en az 1 kez
        return uyuyor && (esles(desen, d + 2, metin, m + 1) || esles(desen, d, metin, m + 1));

    if (sonraki == '?')  // 0 ya da 1 kez
        return esles(desen, d + 2, metin, m) || (uyuyor && esles(desen, d + 2, metin, m + 1));

    // Normal harf: uymalı, sonra ikisi de bir ilerler
    return uyuyor && esles(desen, d + 1, metin, m + 1);
}

bool eslesiyor(string desen, string metin)
{
    return esles(desen, 0, metin, 0);
}

int main()
{
    cout << eslesiyor("abc", "abc") << endl;         // 1
    cout << eslesiyor("abc", "abd") << endl;         // 0
    cout << eslesiyor("a.c", "axc") << endl;         // 1
    cout << eslesiyor("ab*c", "abbbc") << endl;      // 1
    cout << eslesiyor("ab*c", "ac") << endl;         // 1
    cout << eslesiyor("ab+c", "ac") << endl;         // 0
    cout << eslesiyor("colou?r", "color") << endl;   // 1
    cout << eslesiyor("colou?r", "colouur") << endl; // 0
}