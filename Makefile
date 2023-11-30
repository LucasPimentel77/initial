ola: clear
	@echo "=========================================="
	@echo "             PROGRAMA OLA                 "
	@echo "=========================================="
	@echo "Compilando o programa olamundo"
	gcc olamundo.c -o ola
	@echo "Tornando o programa olamundo executável"
	chmod +x ola
	@echo "Executando o programa olamundo"
	./ola
	@echo "=========================================="
clear:
	@echo "=========================================="
	@echo "Removendo os programas compilados"
	@echo "=========================================="
	@echo "Removendo o programa olamundo"	
	rm -f ola
	@echo "=========================================="
help:
	@echo "=========================================="
	@echo "         		AJUDA                    "
	@echo "=========================================="
	@echo "help			| ajuda"
	@echo "ola			| executa mensagem de teste"
	@echo "clear		| apaga códigos compilados"
