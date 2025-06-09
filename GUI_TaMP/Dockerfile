FROM ubuntu:22.04

# Установка зависимостей
RUN apt-get update && apt-get install -y \
    qtbase5-dev qt5-qmake libqt5widgets5 \
    x11-apps libqt5sql5 libqt5sql5-sqlite \
    build-essential cmake

# Рабочая директория
WORKDIR /app

# Копируем проект
COPY . .

# Сборка
RUN mkdir build
WORKDIR /app/build
RUN cmake .. && make

# Запуск GUI-программы (или замени на сервер)
CMD ["./TIMP_KKZM"]


