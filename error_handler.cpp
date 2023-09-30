#include "error_handler.h"

namespace Error 
{
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "Недопустимый код ошибки"),
		ERROR_ENTRY(1, "Системный сбой"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "Ошибка при создании сокета\n"),
		ERROR_ENTRY(101, "Ошибка при привязке сокета к адресу\n"),
		ERROR_ENTRY(102, "Ошибка при прослушивании входящих подключений\n"),
		ERROR_ENTRY(103, "Ошибка открытия файла\n"),
		ERROR_ENTRY(104, "Ошибка записи в файл\n"),
		ERROR_ENTRY(105, "Ошибка при принятии входящего подключения\n"),
		ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "Ошибка чтения данных от клиента\n"),
		ERROR_ENTRY(111, "Ошибка отправки данных клиенту\n"),
		ERROR_ENTRY(112, "Ошибка при создании дочернего процесса\n"),
		ERROR_ENTRY(113, "Ошибка функции waitpid\n"),
		ERROR_ENTRY(114, "Дочерний процесс был прерван внешним сигналом\n"),
		ERROR_ENTRY(115, "Ошибка закрытия сокета\n"),
		ERROR_ENTRY(116, "Ошибка при закрытии файла (-out)"),
		ERROR_ENTRY_NODEF(117),ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF10(120),ERROR_ENTRY_NODEF10(130),ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200),ERROR_ENTRY_NODEF100(300),ERROR_ENTRY_NODEF100(400),ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY_NODEF100(600),ERROR_ENTRY_NODEF100(700),ERROR_ENTRY_NODEF100(800),ERROR_ENTRY_NODEF100(900)
	};

	ERROR geterror(int id)
	{
		if (id > 0 && id < ERROR_MAX_ENTRY) return errors[id];
		else return errors[0];
	}
}