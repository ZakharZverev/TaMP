#include <QtTest/QtTest>          
#include "DatabaseManager.h"    

class TestAuthorization : public QObject {
    Q_OBJECT

private slots:

    void initTestCase();              
    void cleanupTestCase();           

    // Непосредственно сами тесты
    void testNoPassword();            // Проверка: указан логин, но нет пароля
    void testNoUsername();           // Проверка: указан пароль, но нет логина
    void testEmptyFields();          // Проверка: оба поля пустые
};

// Выполняется один раз перед всеми тестами
void TestAuthorization::initTestCase() {
    // Регистрация тестового пользователя с логином testuser и паролем testpass
    DatabaseManager::instance().registerUser("testuser", "testpass");
}

void TestAuthorization::cleanupTestCase() {

}

// Тест: проверка авторизации без пароля
void TestAuthorization::testNoPassword() {
    // Передаём только логин, пароль — пустая строка
    bool result = DatabaseManager::instance().checkLogin("testuser", "");
    QVERIFY(!result);
}

// Тест: проверка авторизации без логина
void TestAuthorization::testNoUsername() {
    // Передаём только пароль, логин — пустая строка
    bool result = DatabaseManager::instance().checkLogin("", "testpass");
    QVERIFY(!result); 
}

// Тест: оба поля пустые
void TestAuthorization::testEmptyFields() {
    bool result = DatabaseManager::instance().checkLogin("", "");
    QVERIFY(!result); 
}

// Запуск главной функции тестов Qt
QTEST_MAIN(TestAuthorization)
#include "unit_test.moc" // Генерация meta-object кода для слотов
