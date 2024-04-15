#include "main.h"

int main(void) {
	logger = log_create("kernelLog.log", "Kernel", 1, LOG_LEVEL_DEBUG);
	int kernelFD = initServer(PORT);
	log_info(logger, "Kernel ready to receive");
	int clientFD = waitClient(kernelFD);
	t_list* lista;
	while (1) {
		int cod_op;
		cod_op = recvOperation(clientFD);
		switch (cod_op) {
		case MESSAGE:
			recvMessage(clientFD);
			break;
		case PACKAGE:
			lista = recvPack(clientFD);
			log_info(logger, "The following values arrived:\n");
			list_iterate(lista, (void*) iterator);
			break;
		case -1:
			log_error(logger, "The client disconnected");
            log_info(logger, "Kernel ready to receive");
			clientFD = waitClient(kernelFD); // Para esperar un nuevo cliente en el caso de que se desconecte el anterior
			break;
		default:
			log_warning(logger,"Unknown operation");
			break;
		}
	}
	return EXIT_SUCCESS;
}

void iterator(char* value) {
	log_info(logger,"%s", value);
}
