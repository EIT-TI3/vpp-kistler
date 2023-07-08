#pragma once

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <numeric>
#include <QJsonObject>
#include <QJsonArray>

#include "fraesung.h"
#include "werkstueck.h"
#include "delist.h"
using namespace testing;

using std::cout;
using std::endl;

TEST(KomponenteTest, Constructor) {
  Komponente k1{3.0, 4.0};
  EXPECT_DOUBLE_EQ(3.0, k1.getX());
  EXPECT_DOUBLE_EQ(4.0, k1.getY());
  Komponente k2{-3.0, -4.0};
  EXPECT_DOUBLE_EQ(0, k2.getX());
  EXPECT_DOUBLE_EQ(0, k2.getY());
}

TEST(KomponenteTest, Output) {
  Komponente k{2.3, 45.7};
  const char* sk = "(2.3, 45.7)";
  std::ostringstream oss;
  k.output(oss);
  EXPECT_STREQ(sk, oss.str().c_str());
}

TEST(BohrungTest, ConstructorDefaultArguments) {
  Bohrung b0{0,0};
  ASSERT_EQ(0.0, b0.getX());
  ASSERT_EQ(0.0, b0.getY());
  ASSERT_EQ(6.0, b0.getDiameter());

  Bohrung b1{3., 4., 3.};
  EXPECT_DOUBLE_EQ(3.0, b1.getX());
  EXPECT_DOUBLE_EQ(4.0, b1.getY());
  EXPECT_DOUBLE_EQ(3.0, b1.getDiameter());

  Bohrung b2{3., 4., 0.0};
  EXPECT_DOUBLE_EQ(6.0, b2.getDiameter());

  Bohrung b3{3., 4., -2.1};
  EXPECT_DOUBLE_EQ(6.0, b3.getDiameter());
}

TEST(BohrungTest, Output) {
  Bohrung b{33.21, 47.02, 6.5};
  const char* sb = "Bohrung: (33.21, 47.02), Durchmesser: 6.5";
  std::ostringstream oss;
  b.output(oss);
  EXPECT_STREQ(sb, oss.str().c_str());
}

TEST(FraesungTest, Constructor) {
  Fraesung f0{0., 0., 0., -2.};
  ASSERT_EQ(0.0, f0.getX());
  ASSERT_EQ(0.0, f0.getY());
  ASSERT_EQ(6.0, f0.getDiameter());
  ASSERT_EQ(0.0, f0.getLength());
  ASSERT_EQ(0.0, f0.getAngle());

  Fraesung f1{3, 4, 2.0, 5, M_PI_4};
  EXPECT_DOUBLE_EQ(3.0, f1.getX());
  EXPECT_DOUBLE_EQ(4.0, f1.getY());
  EXPECT_DOUBLE_EQ(2.0, f1.getDiameter());
  EXPECT_DOUBLE_EQ(5.0, f1.getLength());
  EXPECT_DOUBLE_EQ(M_PI_4, f1.getAngle());
}

TEST(FraesungTest, EndPoints) {
  Fraesung f0{0., 0., 0., -3.5};
  EXPECT_DOUBLE_EQ(0.0, f0.getEndX());
  EXPECT_DOUBLE_EQ(0.0, f0.getEndY());

  Fraesung f1{3, 4, 8., 5, M_PI_4};
  EXPECT_DOUBLE_EQ(3.0 + 2.5 * sqrt(2), f1.getEndX());
  EXPECT_DOUBLE_EQ(4.0 + 2.5 * sqrt(2), f1.getEndY());
}

TEST(FraesungTest, Output) {
  Fraesung f{3, 4, 8., 5, M_PI_4};
  const char* sf =
      "Fraesung mit Start: (3, 4) und Endpunkt: (6.53553, 7.53553),"
      " Durchmesser: 8";
  std::ostringstream oss;
  f.output(oss);
  EXPECT_STREQ(sf, oss.str().c_str());
}

TEST(DeListTest, ConstructEntries) {
  DeList<int> kl;
  Iterator<int> it=kl.begin();
  int a=5;
  ASSERT_EQ(kl.end(), it);
  ASSERT_EQ(kl.end(), kl.begin());
  EXPECT_TRUE(0 == kl.size());
  kl.push_back(a);
  ASSERT_NE(kl.end(), kl.begin());
  EXPECT_TRUE(1 == kl.size());
  it=kl.begin();
  ASSERT_EQ(5, *it);
  kl.push_back(4);
  ++it;
  EXPECT_EQ(4, *it);
  EXPECT_TRUE(2 == kl.size());
}

TEST(DeListTest, CopyConstructAndAssignment) {
    DeList<int> kl;
    kl.push_back(5);
    kl.push_back(4);
    EXPECT_TRUE(2 == kl.size());
    DeList<int> kla(kl);            // Copy-Konstruktor
    kla.push_back(3);
    EXPECT_TRUE(3 == kla.size());
    kl.erase(kl.begin());
    kl.erase(kl.begin());
    kl.erase(kl.begin());           // erase bei leerer Liste
    EXPECT_TRUE(0 == kl.size());
    kl=kla;                         // Zuweisungsop.
    EXPECT_TRUE(3 == kl.size());
    EXPECT_TRUE(12==std::accumulate(kl.begin(), kl.end(), 0));
    kla.erase(kla.begin());
    EXPECT_TRUE(3 == kl.size());
    EXPECT_TRUE(12==std::accumulate(kl.begin(), kl.end(), 0));
    EXPECT_TRUE(2 == kla.size());
    EXPECT_TRUE(7==std::accumulate(kla.begin(), kla.end(), 0));
    kla.clear();
    EXPECT_TRUE(3 == kl.size());
    EXPECT_TRUE(0 == kla.size());
}

TEST(DeListTest, DeleteEntries) {
  DeList<IKomponente *> kl;
  Bohrung b(0,0);
  Fraesung f(1, 0, 1, 1);
  kl.push_back(&b);
  kl.push_back(&f);
  Iterator<IKomponente *> it=kl.begin();
  Iterator<IKomponente *> itb=kl.erase(it);
  EXPECT_TRUE(kl.begin() == itb);  // erstes Element geloescht
  EXPECT_NE(nullptr, *kl.begin());
  EXPECT_TRUE(1 == kl.size());
  itb=kl.erase(kl.begin());
  EXPECT_TRUE(kl.begin() == itb);  // letztes und einziges Element geloescht
  EXPECT_TRUE(0 == kl.size());
}

TEST(DeListTest, EraseAndIterator) {
    DeList<int> kl;
    kl.push_back(5);
    kl.push_back(4);
    Iterator<int> ite=kl.erase(kl.end());
    EXPECT_TRUE(kl.end()==ite);
    kl.push_back(3);
    EXPECT_TRUE(3 == kl.size());
    kl.erase(kl.erase(kl.erase(kl.begin())));
    EXPECT_TRUE(0 == kl.size());
}

TEST(DeListTest, IteratorOperations) {
    DeList<IKomponente *> kl;
    Bohrung b(0,0);
    Fraesung f(1, 0, 1, 1);
    kl.push_back(&b);
    kl.push_back(&f);
    Iterator<IKomponente *> it1=kl.begin(), it2=it1, it3;
    EXPECT_EQ(it1, it2);
    ++it2;
    EXPECT_NE(it1, it2);
    it3=it2;
    ++it3;
    EXPECT_NE(it3, it2);
    EXPECT_EQ(kl.end(), it3);
}

TEST(DeListTest, DeleteEntriesAndAddAfterwards) {
    DeList<IKomponente *> kl;
    Bohrung b{0,0};
    Fraesung f(1, 0, 1, 1);
    kl.push_back(&b);
    kl.push_back(&f);
    Iterator<IKomponente *> it1=kl.begin(), it2=it1, it3=it1;
    ++it2;
    ++it3;
    ++it3;
    EXPECT_EQ(kl.end(), it3);

    EXPECT_TRUE(&b == *it1);  // erstes Element geloescht
    EXPECT_TRUE(it2 == kl.erase(it1));  // erstes Element geloescht
    EXPECT_TRUE(1 == kl.size());
    EXPECT_TRUE(&f == *it2);  // erstes Element geloescht
    EXPECT_TRUE(it3 == kl.erase(it2));  // erstes Element geloescht
    EXPECT_TRUE(0 == kl.size());
    EXPECT_TRUE(it3 == kl.erase(kl.begin()));  // letztes und einziges Element geloescht

    kl.push_back(&f);
    it1=kl.begin();
    EXPECT_NE(kl.end(), it1);
    EXPECT_TRUE(1 == kl.size());
    EXPECT_EQ(&f, *it1);
}

TEST(DeListTest, DeleteEmptyList) {
  DeList<IKomponente *> kl;
  EXPECT_TRUE(0 == kl.size());
  EXPECT_TRUE(kl.begin() == kl.end());
  Iterator<IKomponente *> itb=kl.erase(kl.begin());
  EXPECT_TRUE(kl.end() == itb);  // Element aus leerer Liste loeschen?
}

TEST(DeListTest, IncrementIterator) {
    DeList<IKomponente *> kl;
    Bohrung b(3.2, 0);
    Fraesung f(1, 0, 1, 1);
    kl.push_back(&b);
    kl.push_back(&f);

    Iterator<IKomponente *> it=kl.begin();
    EXPECT_NE(kl.end(), it);
    ++it;
    EXPECT_NE(kl.end(), it);
    ++it;
    EXPECT_EQ(kl.end(), it);
}

TEST(DeListTest, IteratorErase) {
    DeList<IKomponente *> kl;
    Bohrung b(3.2, 0);
    Fraesung f(1, 0, 1, 1);
    kl.push_back(&b);
    kl.push_back(&f);

    Iterator<IKomponente *> it=kl.begin();
    EXPECT_EQ(kl.end(), kl.erase(kl.end()));
    it=kl.erase(it);
    EXPECT_NE(kl.end(), it);
    it=kl.erase(it);
    EXPECT_EQ(kl.end(), it);

}

TEST(WerkstueckTest, Constructor) {
    Werkstueck w0{0., 0., 5., 5.}, w1{3, 4};
    ASSERT_EQ(0.0, w0.getX());
    ASSERT_EQ(0.0, w0.getY());
    ASSERT_EQ(5.0, w0.getHeight());
    ASSERT_EQ(5.0, w0.getWidth());

    ASSERT_EQ(3.0, w1.getX());
    ASSERT_EQ(4.0, w1.getY());
    ASSERT_EQ(1.0, w1.getHeight());
    ASSERT_EQ(1.0, w1.getWidth());
}

TEST(WerkstueckTest, AbsoluteValues) {
    Werkstueck w0{0., 0., 5., 5.}, w1{3, 4}, w2{3,4};
    Fraesung f1{1, 1, 2.0, 2, 0};
    Bohrung b1{0.5, 0.5};

    w0.add(&w1);
    w0.add(&f1);
    w1.add(&w2);
    w2.add(&b1);

    EXPECT_DOUBLE_EQ(6.5, b1.getXAbsolute());
    EXPECT_DOUBLE_EQ(8.5, b1.getYAbsolute());
    EXPECT_DOUBLE_EQ(f1.getX(), f1.getXAbsolute());
    EXPECT_DOUBLE_EQ(f1.getY(), f1.getYAbsolute());
}

TEST(WerkstueckTest, GetChildren) {
    Werkstueck w0(0., 0., 5., 5.), w1(3, 4);
    Fraesung f1(1, 1, 2.0, 2, 0);
    Bohrung b1(0.5, 0.5);

    EXPECT_EQ(nullptr, w0.getChild(0));

    w0.add(&w1);
    w0.add(&f1);
    w1.add(&b1);

    EXPECT_EQ(&w1, w0.getChild(0));
    EXPECT_EQ(&f1, w0.getChild(1));
    EXPECT_EQ(&b1, w1.getChild(0));
    EXPECT_EQ(nullptr, w0.getChild(2));     // ungültige Indizes
    EXPECT_EQ(nullptr, w0.getChild(-1));

    w1.remove(&b1);
    EXPECT_EQ(nullptr, w1.getChild(0));
}

TEST(WerkstueckTest, CalcTotalPath) {
    Werkstueck w0(0, 5, 10, 5), w1(0, 0, 20, 20);
    Fraesung f1(0, 2, 2.0, 2, 0);
    Bohrung b1(0, 0, 1.5);
    Bohrung b2(2, 0, 3);
    Komponente k1(0,0);

    EXPECT_EQ(w0.calcTotalPath(), 0);   // leeres Werkstück
    EXPECT_EQ(f1.calcTotalPath(), 4);
    w0.add(&f1);
    EXPECT_EQ(w0.calcTotalPath(), 8);
    w0.add(&b1);
    EXPECT_EQ(w0.calcTotalPath(), 8);
    w1.add(&b2);
    w1.add(&k1);
    EXPECT_EQ(b2.calcTotalPath(), 0);
    EXPECT_EQ(k1.calcTotalPath(), 0);
    EXPECT_EQ(w1.calcTotalPath(), 4);
    w1.add(&w0);
    EXPECT_EQ(w1.calcTotalPath(), 22);
}

TEST(WerkstueckTest, RemoveTest) {
    Werkstueck w0(0, 3, 10, 5);
    Fraesung f1(0, 2, 2.0, 2, 0);
    Bohrung b1(3, 4, 1.5);
    Komponente k1(3,0);

    w0.add(&b1);

    w0.add(&f1);
    w0.add(&k1);
    w0.remove(&f1);
    // f1 sollte nun nicht mehr in
    // der Werkstückliste sein
    w0.remove(&f1);  // sollte also nichts mehr machen

    EXPECT_EQ(w0.calcTotalPath(),12);

}

TEST(WerkstueckTest, HandleNullptr) {
    Werkstueck w0(3, 4, 10, 5);
    Bohrung b1(3, 4, 1.5);
    Bohrung k(1, 0);

    w0.add(nullptr);    // sollte nichts hinzufuegen
    w0.remove(&b1);     // sollte nichts entfernen

    w0.add(&b1);

    EXPECT_EQ(&b1, w0.getChild(0));
    w0.remove(&k);
    EXPECT_EQ(&b1, w0.getChild(0));
    EXPECT_EQ(w0.calcTotalPath(),10);

    w0.remove(nullptr);  // sollte nichts entfernen
    w0.remove(&b1);  // sollte b1 entfernen

    EXPECT_EQ(w0.calcTotalPath(),0);

}

TEST(WerkstueckTest, DoubleInsert) {
    Werkstueck w0(3, 4, 10, 5);
    Bohrung b1(3, 4, 1.5);
    Bohrung k(1, 0);

    EXPECT_EQ(k.getParent(),nullptr);
    EXPECT_EQ(b1.getParent(),nullptr);
    w0.add(&b1);
    EXPECT_NE(b1.getParent(),nullptr);
    // Wenn getParent von b1 gesetzt wurde, darf
    // die Komponente nicht mehr hinzugefügt werden.
    w0.add(&b1);

    EXPECT_EQ(&b1, w0.getChild(0));
    EXPECT_EQ(nullptr, w0.getChild(1));
    EXPECT_EQ(w0.calcTotalPath(),10);

    w0.remove(&k);  // sollte nichts entfernen
    w0.remove(&b1);  // sollte b1 entfernen
    EXPECT_EQ(k.getParent(),nullptr);
    EXPECT_EQ(b1.getParent(),nullptr);
    EXPECT_EQ(nullptr, w0.getChild(0));

    EXPECT_EQ(w0.calcTotalPath(),0);

}

TEST(WerkstueckTest, OptimizePath) {
    Werkstueck w0(0, 5, 10, 5);
    Fraesung f1(0, 2, 2.0, 2, 0);
    Bohrung b1(2, 2, 1.5);
    Komponente k1(2,0);

    w0.add(&b1);
    w0.add(&f1);
    w0.add(&k1);
    EXPECT_GT(w0.calcTotalPath(),12);
    EXPECT_EQ(w0.getChild(1),&f1);
    w0.optimizePath();
    EXPECT_EQ(w0.calcTotalPath(),12);
    // b1 muss jetzt das 2. Element sein
    EXPECT_EQ(w0.getChild(1),&b1);

}

TEST(WerkstueckTest, OptimizePathOnEmpty) {
    Werkstueck w0(0, 5, 10, 5);
    EXPECT_EQ(w0.calcTotalPath(),0);
    EXPECT_EQ(w0.getChild(0), nullptr);
    w0.optimizePath();
    EXPECT_EQ(w0.calcTotalPath(),0);
    EXPECT_EQ(w0.getChild(1), nullptr);
    EXPECT_EQ(w0.getChild(-1), nullptr);
    EXPECT_EQ(w0.getChild(100), nullptr);
    EXPECT_EQ(w0.getChild(-100), nullptr);
}

TEST(JSONTest, LeafObjectTest) {
    Fraesung f1(0, 2, 1, 3, M_PI_4);
    Bohrung b1(1, 2, 1.5);
    Komponente k1(2,0);

    QJsonObject tmp=k1.toJson();
    EXPECT_EQ(tmp["type"].toString().toStdString(), "Komponente");
    EXPECT_EQ(tmp["x"].toDouble(), 2);
    EXPECT_EQ(tmp["y"].toDouble(), 0);
    EXPECT_EQ(tmp["hasParent"].toBool(), false);
    tmp=b1.toJson();
    EXPECT_EQ(tmp["type"].toString().toStdString(), "Bohrung");
    EXPECT_EQ(tmp["x"].toDouble(), 1);
    EXPECT_EQ(tmp["y"].toDouble(), 2);
    EXPECT_EQ(tmp["diameter"].toDouble(), 1.5);
    EXPECT_EQ(tmp["hasParent"].toBool(), false);
    tmp=f1.toJson();
    EXPECT_EQ(tmp["type"].toString().toStdString(), "Fraesung");
    EXPECT_EQ(tmp["x"].toDouble(), 0);
    EXPECT_EQ(tmp["y"].toDouble(), 2);
    EXPECT_EQ(tmp["diameter"].toDouble(), 1);
    EXPECT_EQ(tmp["length"].toDouble(), 3);
    EXPECT_EQ(tmp["angle"].toDouble(), M_PI_4);
    EXPECT_EQ(tmp["hasParent"].toBool(), false);
}

TEST(JSONTest, CompositeObjectTest) {
    Werkstueck w0(0, 5, 10, 5);
    Bohrung b1(1, 2, 1.5);
    Komponente k1(2,0);
    QJsonObject tmp=w0.toJson();

    EXPECT_EQ(tmp["pathIsOptimized"].toBool(), false);
    w0.add(&b1);
    tmp=k1.toJson();
    EXPECT_EQ(tmp["hasParent"].toBool(), false);
    tmp=b1.toJson();
    EXPECT_EQ(tmp["hasParent"].toBool(), true);
    w0.add(&k1);

    tmp=w0.toJson();
    EXPECT_EQ(tmp["type"].toString().toStdString(), "Werkstueck");
    EXPECT_EQ(tmp["x"].toDouble(), 0);
    EXPECT_EQ(tmp["y"].toDouble(), 5);
    EXPECT_EQ(tmp["height"].toDouble(), 10);
    EXPECT_EQ(tmp["width"].toDouble(), 5);
    EXPECT_EQ(tmp["hasParent"].toBool(), false);
    EXPECT_EQ(tmp["components"].isArray(), true);
    QJsonArray arr=tmp["components"].toArray();
    EXPECT_EQ(arr.count(), 2);

    w0.remove(&b1);
    tmp=b1.toJson();
    EXPECT_EQ(tmp["hasParent"].toBool(), false);

}

TEST(JSONTest, OptimizedPath) {
    Werkstueck w0(0, 5, 10, 5), w1(0, 5, 10, 5);
    Bohrung b1(1, 2, 1.5);
    Komponente k1(2,0);
    QJsonObject tmp=w0.toJson();

    EXPECT_EQ(tmp["pathIsOptimized"].toBool(), false);
    w0.add(&b1);

    w0.optimizePath();
    w1.remove(&b1);         // darf nichts entfernen, somit auch nicht
                            // parent zuruecksetzen.
                            //    auch pathIsOptimized muss true bleiben
    EXPECT_EQ(&w0, b1.getParent());

    w1.add(&b1);         // darf b1 nicht mehr hinzufuegen, somit auch nicht
                         // parent aendern.
                         //    auch pathIsOptimized muss true bleiben
    EXPECT_EQ(&w0, b1.getParent());
    tmp=w0.toJson();
    EXPECT_EQ(tmp["pathIsOptimized"].toBool(), true);

    w0.add(&k1);
    tmp=w0.toJson();
    EXPECT_EQ(tmp["pathIsOptimized"].toBool(), false);

    w0.optimizePath();
    w0.remove(&w1);     // Es darf nicht geloescht werden
                        // da w1 nicht in w0.
                        //    auch pathIsOptimized muss true bleiben

    w1.remove(&b1);      // b1 wird nicht aus w1 geloescht,
                         // da es nicht in w1 stecken darf,
                         // somit darf sich auch nicht
                         // parent aendern.
                         //    auch pathIsOptimized muss true bleiben
    EXPECT_EQ(&w0, b1.getParent());
    tmp=w0.toJson();
    EXPECT_EQ(tmp["pathIsOptimized"].toBool(), true);

    w0.remove(&b1);
    tmp=w0.toJson();
    EXPECT_EQ(tmp["pathIsOptimized"].toBool(), false);

}

