# multithreading
Решение проблемы доступа к общим ресурсам среди потоков.

Задача: решение проблемы с обедающими философами, у каждого только одна вилка. При этом кушать могут только с двумя.

Как запустить: make в каждой папке.

Запуск с аргументами: 1ый аргумент - количество философов,
2ой агрумент - время для смерти без еды, 3ий агрумент - время еды, 4ый - время для сна, 
5ый аргумент (ОПЦИОНАЛЬНО) количество раз сколько должен поесть каждый философ.

Минимальное количество философов: 2

Максимальное количество философов: 200

Пример запуска:

		./philo_one 5 800 200 200 

PHILO_ONE:

Применен mutex для синхронизации потоков. Один родительский процесс, все философы представлены параллельными потоками.

PHILO_TWO:

Используются семафоры, один родительский процесс, философы в параллельных потоках.

PHILO_THREE:

Каждый философ отдельный процесс, обмен данными происходит через семафоры.