#pragma once

class Observator {
  public:
    virtual void updateaza() = 0;
};

#include <vector>
#include <algorithm>
using std::vector;

class Observabil {
  private:
    vector<Observator*> observatoare;

  public:
    void adaugaObservatore(Observator* obs) {
      observatoare.push_back(obs);
    }

    void stergeObservatore(Observator* obs) {
      observatoare.erase(std::remove(observatoare.begin(), observatoare.end(), obs),observatoare.end());

    }

    void notifica(){
      for (auto obs : observatoare) {
        obs->updateaza();
      }
    }
};