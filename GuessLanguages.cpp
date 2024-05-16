//
// Implementation of the GuessLanguages function
//
// Author: Max Benson
// Date: 09/01/2022
// Modifier: Ilya Bukhalau
// Modification Date: 11/28/22
//

#include <iostream>
using std::cout;
using std::endl;

#include "GuessLanguages.h"

void GuessLanguages(set<Corpus> corpora) {
    string text;
    string language;
    KGrams kgrams1;
    KGrams kgrams2;
    KGrams kgrams3;
    KGrams kgrams4;
    KGrams kgrams5;
    KGrams kgrams6;
    KGrams kgrams7;
    KGrams kgrams8;
    KGrams kgrams9;
    KGrams kgrams10;
    KGrams kgrams11;
    KGrams kgrams12;
    KGrams kgrams13;
    KGrams kgrams14;
    KGrams kgrams15;

    cout << "1. What language is this written in?" << endl;
    //Намрын бороо зөөлөн шиврэхэд аав минь дуртай
    //Насыг нь зөөж буцсаар л байгаа шувуудад хайртай
    //Өөрөө өтлөвч, орчлонд үлдэнэ гэж надад хайртай
    //Өдрөөс өдөрт холдсоор л байгаа аавдаа би хайртай
    //Шар наран улам алслаад л
    text = "Намрын бороо зөөлөн шиврэхэд аав минь дуртай\n"
           "Насыг нь зөөж буцсаар л байгаа шувуудад хайртай\n"
           "Өөрөө өтлөвч, орчлонд үлдэнэ гэж надад хайртай\n"
           "Өдрөөс өдөрт холдсоор л байгаа аавдаа би хайртай\n"
           "Шар наран улам алслаад л";
    kgrams1.CreateProfileFromText(text, 3, 2000);
    language = Corpus::GuessLanguageOf(kgrams1.Profile(), corpora);
    cout << "The language probably is " << language << endl << endl;

    cout << "2. What language is this written in?" << endl;
    text = "아리랑, 아리랑, 아라리요…\n"
           "아리랑 고개로 넘어간다.\n"
           "나를 버리고 가시는 님은\n"
           "십리도 못가서 발병난다.\n"
           "청천하늘엔 잔별도 많고,\n"
           "우리네 가슴엔 희망도 많다.\n"
           "저기 저 산이 백두산이라지,\n"
           "동지 섣달에도 꽃만 핀다.";
    kgrams2.CreateProfileFromText(text, 3, 2000);
    language = Corpus::GuessLanguageOf(kgrams2.Profile(), corpora);
    cout << "The language probably is " << language << endl << endl;

    cout << "3. What language is this written in?" << endl;
    text = "Penei ka manao ana o kekahi poe. I ke kaua ana o kekahi aina\n"
           "me kekahi aina, o ka poe i hee, makau lakou o lukuia mai a holo\n"
           "wale lakou ma ka moana, a loaa kahi aina, a noho iho la malaila,\n"
           "a pela hou no, a hiki no na kanaka ma na moku a pau. I ka manao\n"
           "o kekahi poe, ua pupuhi wale ia na waa i holo ma ka moana a pae\n"
           "wale aku i kekahi aina. Ua manao wale ia keia mau mea, aole i\n"
           "maopopo.";
    kgrams3.CreateProfileFromText(text, 3, 2000);
    language = Corpus::GuessLanguageOf(kgrams3.Profile(), corpora);
    cout << "The language probably is " << language << endl << endl;

    cout << "4. What language is this written in?" << endl;
    text = "Negema wangu binti, mchachefu wa sanati upulike wasiati asa\n"
           "ukanzingatia. Maradhi yamenshika hatta yametimu mwaka sikupata\n"
           "kutamka neno lema kukwambia. Ndoo mbee ujilisi na wino na\n"
           "qaratasi moyoni nina hadithi nimependa kukwambia.";
    kgrams4.CreateProfileFromText(text, 3, 2000);
    language = Corpus::GuessLanguageOf(kgrams4.Profile(), corpora);
    cout << "The language probably is " << language << endl << endl;

    cout << "5. What language is this written in?" << endl;
    text = "床前明月光\n"
           "疑是地上霜\n"
           "举头望明月\n"
           "低头思故乡";
    kgrams5.CreateProfileFromText(text, 3, 2000);
    language = Corpus::GuessLanguageOf(kgrams5.Profile(), corpora);
    cout << "The language probably is " << language << endl << endl;

    cout << "6. What language is this written in?" << endl;
    text = "გულისფანცქალით მივდიოდით მხარეში, საიდანაც ვიწყებდით ძველი\n"
           "წელთაღრიცხვის საიდუმლოებებით მოცულ მიწისზედა თუ მიწისქვეშა\n"
           "ტალანებსა და გამოქვაბულებში ძრომა-ხეტიალს.";
    kgrams6.CreateProfileFromText(text, 3, 2000);
    language = Corpus::GuessLanguageOf(kgrams6.Profile(), corpora);
    cout << "The language probably is " << language << endl << endl;

    cout << "7. What language is this written in?" << endl;
    text = "ᎤᎵᏍᏔᏴᏗ ᎦᎵᏙᏗ ᏭᎷᏤᎢ, ᎤᏗᏔᎮ ᎦᏁᎲ, ᎤᏲᏏᏍᎩ ᎤᏗᏔᎮ ᎤᏅᏗ ᏃᎴ ᎤᎩᏍᏙᎡ\n"
           "ᏑᎾᎴ ᎠᎩᏍᏗ ᎤᏂᏑᎸᏓ. ᎣᏍᏓ ᏄᎵᏍᏔᏁᎮ ᎤᏩᏌ ᎤᏪᏅᏒ ᎡᏙᎲ. ᎦᏅᏆᎶᏍᏗ ᏭᏴᎮ\n"
           "ᏣᏄᏏ ᏃᎴ ᏣᏁᎳ ᎠᏂᏎᏂᏏ ᏴᎩ, ᎣᏍᏓ ᏄᏩᏁᎴ ᎠᏦᏴ.";
    kgrams7.CreateProfileFromText(text, 3, 2000);
    language = Corpus::GuessLanguageOf(kgrams7.Profile(), corpora);
    cout << "The language probably is " << language << endl << endl;

    cout << "8. What language is this written in?" << endl;
    text = "\n                                          يُعتقد بأن ضابطة في الجيش البريطاني تدعى بريت تشاندي أصبحت أول"
           "\n    امرأة من أصول آسيوية تُكملُ رحلة استكشافية فردية عبر"
           "\n    القارة القطبية الجنوبية.";
    kgrams8.CreateProfileFromText(text, 3, 2000);
    language = Corpus::GuessLanguageOf(kgrams8.Profile(), corpora);
    cout << "The language probably is " << language << endl << endl;

    cout << "9. What language is this written in?" << endl;
    text = "Akyinkyinakyinkyin ama mahu nneɛma,\n"
           "Asante Bonwire Kente nwene deɛ,\n"
           "Manhu bi da o,\n"
           "Kwame nim adeɛ yɔ\n"
           "Ne kente nwono na abɔ me gye\n"
           "Ne nsa; ne nan, n’asadua saa nie.\n";
    kgrams9.CreateProfileFromText(text, 3, 2000);
    language = Corpus::GuessLanguageOf(kgrams9.Profile(), corpora);
    cout << "The language probably is " << language << endl << endl;

    cout << "10. What language is this written in?" << endl;
    text = "ਤੁਹਾਡੇ ਲਈ ਸ਼ੁਭ ਫਲ ਦੇਣ ਵਾਲਾ ਹੈ। ਆਪਣੀ ਮਿੱਠੀ ਬਾਣੀ ਨਾਲ ਕਿਸੇ ਦਾ ਵੀ ਦਿਲ ਤੁਸੀਂ ਜਿੱਤ\n"
           "ਸਕਦੇ ਹੋ। ਤੁਹਾਡੇ ਕੰਮਾਂ ਦੀ ਪੂਰਤੀ ਹੋ ਸਕਦੀ ਹੈ। ਪਰਿਵਾਰ ਵਿੱਚ ਆਨੰਦ ਦਾ ਮਾਹੌਲ\n"
           "ਰਹੇਗਾ। ਰਿਸ਼ਤੇਦਾਰਾਂ ਦੇ ਨਾਲ ਸੁਖ ਨਾਲ ਸਮਾਂ ਗੁਜ਼ਰੇਗਾ। ਆਰਥਿਕ ਲਾਭ ਹੋਣ ਦੀ ਸੰਭਾਵਨਾ\n"
           "ਹੈ। ਬੌਧਿਕ ਚਰਚਾ ਵਿੱਚ ਹਿੱਸਾ ਲਓਗੇ। ਆਯਾਤ – ਨਿਰਯਾਤ ਨਾਲ ਸਬੰਧਿਤ ਵਿਸ਼ਿਆਂ\n"
           "ਵਿੱਚ ਸਫਲਤਾ ਪ੍ਰਾਪਤ ਹੋਵੇਗੀ।";
    kgrams10.CreateProfileFromText(text, 3, 2000);
    language = Corpus::GuessLanguageOf(kgrams10.Profile(), corpora);
    cout << "The language probably is " << language << endl << endl;

    cout << endl << "Your language identifier probably isn't perfect..." << endl << endl;

    cout << "11. This text by Robert Burns is written in Scots. What language does your program say it’s written in?" << endl;
    cout << "(Sometimes, the trigrams from a text in one language will closely match the trigrams from a related language.)" << endl;
    text = "And there's a hand, my trusty fiere! and gie's a hand o' thine! And we'll\n"
           "tak' a right gude-willie waught, for auld lang syne.";
    kgrams11.CreateProfileFromText(text, 3, 2000);
    language = Corpus::GuessLanguageOf(kgrams11.Profile(), corpora);
    cout << "The language probably is " << language << endl << endl;

    cout << "12. This text is written in English. What language does your program say it’s written in? " << endl;
    cout << "(Short texts can have trigrams that do not match the general trigram distribution for texts in that language.)" << endl;
    text = "San Jose is in Santa Clara County, California.";
    kgrams12.CreateProfileFromText(text, 3, 2000);
    language = Corpus::GuessLanguageOf(kgrams12.Profile(), corpora);
    cout << "The language probably is " << language << endl << endl;

    cout << "13. This text is written in English. What language does your program say it’s written in?" << endl;
    cout << "(Trigrams are case-sensitive. We derived the English trigrams from texts that were written in formal" << endl;
    cout << "English, in which it’s very unusual to see long strings of capitalized letters. As a result, this text will be a low match against English.)" << endl;
    text = "IT WAS THE BEST OF TIMES, IT WAS THE WORST OF TIMES, IT WAS THE AGE OF\n"
           "WISDOM, IT WAS THE AGE OF FOOLISHNESS, IT WAS THE EPOCH OF BELIEF, IT\n"
           "WAS THE EPOCH OF INCREDULITY, IT WAS THE SEASON OF LIGHT, IT WAS THE\n"
           "SEASON OF DARKNESS, IT WAS THE SPRING OF HOPE, IT WAS THE WINTER OF\n"
           "DESPAIR, WE HAD EVERYTHING BEFORE US, WE HAD NOTHING BEFORE US, WE WERE\n"
           "ALL GOING DIRECT TO HEAVEN, WE WERE ALL GOING DIRECT THE OTHER WAY – IN\n"
           "SHORT, THE PERIOD WAS SO FAR LIKE THE PRESENT PERIOD, THAT SOME OF ITS\n"
           "NOISIEST AUTHORITIES INSISTED ON ITS BEING RECEIVED, FOR GOOD OR FOR\n"
           "EVIL, IN THE SUPERLATIVE DEGREE OF COMPARISON ONLY.";
    kgrams13.CreateProfileFromText(text, 3, 2000);
    language = Corpus::GuessLanguageOf(kgrams13.Profile(), corpora);
    cout << "The language probably is " << language << endl << endl;

    cout << "14. This song is written in Nepali. What language does your program say it’s written in?" << endl;
    cout << "(Nepali is traditionally written with Devanagari script, and we used those texts to get our trigrams." << endl;
    cout << "In this example, it’s transliterated using a Latin-derived alphabet. Therefore, this will have a low match with Nepali.)" << endl;
    text = "Rātō ṭikā nidhārmā ṭalakkai ṭalkiyō\n"
           "ḍhākā ṭōpī śiraimā ḍhalakkai ḍhalkiyō\n"
           "rātō ṭikā nidhārmā ṭalakka ṭalkiyō\n"
           "chāti bhitra māyākō āgō salkiyō\n"
           "ē bijulikō tār tār tār tār\n"
           "phursad bha'ē ē hajur bhēṭauṅ śanivār\n"
           "phursad bha'ē ē hajur bhēṭauṅ śanivār\n"
           "ḍhākā ṭōpī śiraimā ḍhalakka ḍhalkiyō\n"
           "māyā khēlnē khēlāḍī jhulukkai jhulkiyō\n"
           "ē bijulikō tār tār tār tār\n"
           "phursad chaina ē hajur ā'uṅdō śanivār\n"
           "phursad chaina ē hajur ā'uṅdō śanivār";
    kgrams14.CreateProfileFromText(text, 3, 2000);
    language = Corpus::GuessLanguageOf(kgrams14.Profile(), corpora);
    cout << "The language probably is " << language << endl << endl;
}
