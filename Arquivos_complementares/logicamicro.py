import sys


def main():
    //inicia sistema
    //carrega senha padrao
    //controle de tentativas
    nTentativas = 0
    while(nTentativas <= 3):
        print(f"Tentativas restantes: {3 - nTentativas}")
        //Verificação de digitação
        //Mostrar mensagem "Insira a Senha"
        while(not enterPressed):
            //envia para display o número selecionado
            //armazena o número digitado até então
            //envia som bip curto caso uma tecla seja pressionada

        if(senhaDigitada = Senha):
            //envia sinal para abrir
            //envia som de 3 bips curtos para dizer que a senha está correta
            //Mostrar mensagem "Cofre Aberto"
        else:
            //envia som longo para dizer que a senha está incorreta
            //limpa display e senhaDigitada
            //Mostrar mensagem "Senha incorreta"
        nTentativas = nTentativas + 1
        if((3 - nTentativas) = 0):
            //Mostrar mensagem "Cofre travado" e a mensagem a seguir
            print(f("Teclado Bloqueado por 20 segundos"))
            



if __name__ == "__main__":
    main()
