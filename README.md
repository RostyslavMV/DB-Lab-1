# DB-Lab-1
Робота з структурованими файлами з індексним доступом (без СУБД).
Мета роботи – навчитися працювати з структ. файлами без використання СУБД на основі
лише мови С.
В якості предметної області слід вибрати ту, яку ви обрали для ER-моделі.
Потрібно створити два чи більше файлів з тестовими даними та доповнити їх наступними
функціями:
1. функція читання заданого запису та заданих підзаписів на основі прямого
індексного доступу; (get-m, get-s)
2. функція вилучення заданого запису чи заданого підзапису; при вилученні запису
необхідно вилучати всі його підзаписи; (del-m, del-s)
3. функція оновлення значення заданого поля заданого запису чи заданого підзапису;
(update-m, update-s)
4. функція внесення запису та/чи підзаписів в файли (можливо доведеться розрізняти
ініціальне внесення даних та поточне) (insert-m, insert-s).
5. функція підрахунку кількості записів, підзаписів загалом, а також кількості
підзаписів для кожного запису.
6. 2 утиліти (ut-m, ut-s) читання та друку всіх полів (включаючи службові) мастер-
файлу та підлеглого файлу.
