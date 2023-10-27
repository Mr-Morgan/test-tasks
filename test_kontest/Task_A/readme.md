/**
 * Эта программа написана для решения задачи А "Хитрый шифр" на платформе контест:
 * Автор: А. Зюльковский - 26.10.2023
 * Cypher - Версия 1.0
 *
 * Описание:
 *     Логика программы: считываем n, выполняем расчет по первому кандидату, выводим 
 * его шифр,считываем данные следующего кандидата и т.д
 *     Для временного хранения данных кандидата целесообразно написать отдельный тип 
 * с полями: первоначальная строка, кол-во разных букв, сумма цифр дня и месяца, 
 * номер первой буквы в алфавите и методом возвращающий шифр
 *     Посчитать кол-во разных символов можно сделав массив целых чисел на 52 элемента
 * (размер алфавита) посчитать сколько непустых элементов в массиве после заполнения
 *     Индекс первой буквы получается как разность буквы и первого символа алфавита
 * (возможно +1, т.к индексация начинается не с нуля, а с единицы)
 *     Логика перевода в 16-ю систему с сохранением 3-х разрядов:
 * цикл for(..; i < 3; ..) в цикле заполняем строку с конца инициализированную 
 * символами '0' 
 *     Конструктор инициализируется строкой и заполняет поля (номер первого символа, 
 * кол-во разных, сумма цифр дня и месяца) 
 *     В main считывается строка определяется количество итераций
 * 
 * Сложность:
 * - Сложность времени: O()
 * - Сложность памяти: O()
 *
 * Недостатки:
 * - 
 * - 
 */
