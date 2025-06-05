#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCryptographicHash>

class DatabaseManager
{
public:
    static DatabaseManager& instance()
    {
        static DatabaseManager instance;
        return instance;
    }

    bool openDatabase()
    {
        if (db.isOpen())
            return true;

        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("users.db");

        if (!db.open()) {
            qDebug() << "Database error: " << db.lastError().text();
            return false;
        }

        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS users ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "username TEXT UNIQUE, "
                   "password_hash TEXT, "
                   "role TEXT DEFAULT 'user')");

        return true;
    }

    QString hashPassword(const QString& password)
    {
        QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
        return QString(hash.toHex());
    }

    bool checkLogin(const QString& username, const QString& password)
    {
        QSqlQuery query;
        query.prepare("SELECT password_hash FROM users WHERE username = :username");
        query.bindValue(":username", username);

        if (query.exec()) {
            if (query.next()) {
                QString storedHash = query.value(0).toString();
                QString inputHash = hashPassword(password);
                return storedHash == inputHash;
            }
        } else {
            qDebug() << "Login query error:" << query.lastError().text();
        }
        return false;
    }

    bool registerUser(const QString& username, const QString& password, const QString& role = "user")
    {
        QSqlQuery query;
        query.prepare("INSERT INTO users (username, password_hash, role) VALUES (:username, :password_hash, :role)");
        query.bindValue(":username", username);
        query.bindValue(":password_hash", hashPassword(password));
        query.bindValue(":role", role);

        if (!query.exec()) {
            qDebug() << "Register query error:" << query.lastError().text();
            return false;
        }
        return true;
    }

    QString getUserRole(const QString& username)
    {
        QSqlQuery query;
        query.prepare("SELECT role FROM users WHERE username = :username");
        query.bindValue(":username", username);

        if (query.exec() && query.next()) {
            return query.value(0).toString();
        } else {
            qDebug() << "Role fetch error:" << query.lastError().text();
            return "unknown";
        }
    }


private:
    DatabaseManager() { openDatabase(); }
    ~DatabaseManager() { if (db.isOpen()) db.close(); }

    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H

