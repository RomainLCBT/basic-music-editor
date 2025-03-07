#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include<cstdint>

using namespace std;

struct Note {
    string name;
    double frequency;
};


double getFrequency(const string& noteName) { //on prédéfini les fréquences des notes 
    
    static const map<string, double> noteFrequencies = {

        {"do", 261.63}, 
        {"re", 293.66}, 
        {"mi", 329.63},
        {"fa", 349.23}, 
        {"sol", 392.00}, 
        {"la", 440.00}, 
        {"si", 493.88}

    };

    return noteFrequencies.at(noteName);
}





// fonction pour générer une sinusoïde pour une note donnée
vector<int16_t> generateWave(double frequency, double duration, int sampleRate) {
    vector<int16_t> wave;
    const double amplitude = 32760; // amplitude maximale pour int16_t comme ça on évite le clipping
    const double tau = 2.0 * M_PI; //pi

    for (int i = 0; i < sampleRate * duration; ++i) {
        double time = static_cast<double>(i) / sampleRate;
        int16_t sample = static_cast<int16_t>(amplitude * sin(tau * frequency * time));
        wave.push_back(sample);
    }
    return wave;
}




void writeWavFile(const string& filename, const vector<int16_t>& data, int sampleRate) {
    ofstream file(filename, ios::binary); // ouverture du fichier en binaire 

    // en-tête du fichier WAV
    file.write("RIFF", 4);
    int fileSize = 36 + data.size() * 2;
    file.write(reinterpret_cast<const char*>(&fileSize), 4);
    file.write("WAVEfmt ", 8);
    int fmtChunkSize = 16;
    file.write(reinterpret_cast<const char*>(&fmtChunkSize), 4);
    short audioFormat = 1; // PCM

    file.write(reinterpret_cast<const char*>(&audioFormat), 2);
    short numChannels = 1; // Mono
    file.write(reinterpret_cast<const char*>(&numChannels), 2);

    file.write(reinterpret_cast<const char*>(&sampleRate), 4);
    int byteRate = sampleRate * numChannels * sizeof(int16_t);
    file.write(reinterpret_cast<const char*>(&byteRate), 4);
    short blockAlign = numChannels * sizeof(int16_t);
    file.write(reinterpret_cast<const char*>(&blockAlign), 2);
    short bitsPerSample = sizeof(int16_t) * 8;
    file.write(reinterpret_cast<const char*>(&bitsPerSample), 2);
    file.write("data", 4);
    int dataSize = data.size() * sizeof(int16_t);
    file.write(reinterpret_cast<const char*>(&dataSize), 4);





    // écriture des données audio
    file.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(int16_t));
}

int main() {

    string input;

    cout <<" entrez le nom de votre fichier texte\n" << endl;

    cin >> input;

    ifstream inputFile(input);

    if (!inputFile.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier"<< input << endl;
        return 1;
    }

    vector<Note> notes;
    int bpm;
    inputFile >> bpm;

    string noteName;

    while (inputFile >> noteName) {
        Note note;
        note.name = noteName;
        note.frequency = getFrequency(noteName);
        notes.push_back(note);
    }

    inputFile.close();

    int sampleRate = 44100; // fréquence d'échantillonnage par défaut
    double durationPerBeat = 60.0 / bpm; //calcul d'un battement

    vector<int16_t> audioData;
    for (const auto& note : notes) {
        vector<int16_t> wave = generateWave(note.frequency, durationPerBeat, sampleRate);

        audioData.insert(audioData.end(), wave.begin(), wave.end());
    }

    writeWavFile("output.wav", audioData, sampleRate);
    cout << "Fichier audio généré : output.wav" << endl;

    return 0;
}
