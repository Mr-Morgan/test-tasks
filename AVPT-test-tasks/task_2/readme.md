### Алгоритм решения Задачи №2 
1. Поля класса:
    - указатель на буффер;
    - целое значение сдвига, инициилизированное по умолчанию нулем;
    - константные индексы начала новых блоков;
    - массив констант для наложения масок.
2. Методы класса:
    - Конструктор принимающий буффер и сдвиг (со значением по умолчанию 0);
    - Конструктор принимающий ссылку на объект класса;
    - short getdata() - для чтения
    - void putdata() - для записи
    - unsigned gethead(char*) - возвращает длину блока в байтах, модифицирует указатель на старший байт блока
    - unsigned getfixed(char*)
    - unsigned getvariable(char*)

> 	Буффер - это последовательность N байт. 0-й байт - крайний правый. 
>       Смещение буффера относительно его начала (начального байта) выполняется в момент чтения/записи, переменная start (в битах) увеличивается на количество бит (сдвиг*8) 
> соответствующих сдвигу. С самим буффером при этом ничего не происходит.
 >
>	Блоки и их размеры заранее предопределены: заголовок 10 байт [0;9], фиксированная часть 6 байт [10;15], и переменная часть [16; N).
>       Если сдвиг сокращает количество байт до 15 и меньше, то буффер будет считаться невалидным. Так же при инициализации необходимо проверить длину буффера.
