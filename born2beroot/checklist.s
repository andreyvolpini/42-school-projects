Born2beRoot – Checklist Prático até o Monitoring.sh

=================================================
1. Criar a Máquina Virtual (VM) no VirtualBox ✅
=================================================
- Criar nova VM Debian 64 bits.
- 2 GB de RAM.
- 20 GB HD virtual (VDI).
- Configurar para inicializar pela ISO do Debian.
- NAT
- 1 CPU
-» hostname - login
-» dominio - ""

=================================================================
2. Particionamento Manual – LVM Criptografado e /boot Separado ✅
=================================================================
-» Selecionar HD - "Yes"
- /boot: 512 MB, ext4, flag iniciável ativada, NÃO criptografada.

-» configure encryeted volumes - "Yes"
-» para finalizar partições - "No" (mais rápido, Yes apenas necessário em disco real/antigo)
-» configurar partições - "Yes"
- Restante do disco: partição primária, tipo “volume físico para criptografia” (LUKS).
- Definir senha para criptografia.

-» create volume group - "vg-root"
- Dentro do volume criptografado, criar grupo LVM (ex: vg-root).
  - LV / (ex: 7 GB, ext4) - "root"
  - (opcional) LV swap (1-2 GB, tipo swap) - "swap"
  - LV /home (restante, ext4) - "home"

-» finish - "Yes"

===========================================
3. Instalar Debian sem Interface Gráfica ✅
===========================================
-» Configure the package manager - "No"
-» deb.debian.org
-» proxy - ""
-» Configure popularity-contest - "No"

-» Apenas od dois ultimos selecionados - "servidor SSH" "utilitários de sistema padrão"
- Instalar Debian, modo texto.
- Só marcar utilitários do sistema e servidor SSH.
- NÃO instalar ambiente gráfico (GNOME, Xfce, etc).

-» Install the GRUB - "Yes"
-» dev/sata

=============================================================
4. Configuração Inicial – Hostname, Usuário, Grupos e Sudo ✅
=============================================================
- Durante a instalação, criar usuário com login da 42
- Após instalar:
  
  - Editar /etc/hostname e /etc/hosts para colocar seu_login42
  -» sudo hostname seu_login42
  -» saber suas permições
    - groups
    -» como não tinha permição, utilizei:
        su - (entrar no modo root, "exit" para sair do modo root)
        hostname seu_login42 (isso edita temporariamente)

        para editar permante, que é exigido:
            sudo nano etc/hostname e /etc/hosts

        -»sudo reboot
        
-» sudo -V (verificar se está instalado)
  - Instalar sudo se não tiver:
      apt update
      apt install sudo

  - Criar grupo user42:
      sudo groupadd user42

  - Adicionar usuário aos grupos sudo e user42:
      sudo usermod -aG sudo seu_login
      sudo usermod -aG user42 seu_login

      -»sudo reboot para atualizar os grupos adicionados

=================================
5. Ativar e Verificar AppArmor ✅
=================================
- Verificar se já está instalado:
    -» sudo systemctl status apparmor
        (ver se marca como “active (exited)” ou “active (running)”)
    -» sudo aa-status
        “apparmor module is loaded”
        Perfis estão em enforce mode

- Instalar (se necessário):
    sudo apt install apparmor apparmor-profiles apparmor-utils

- Ativar no boot:
    sudo systemctl enable apparmor
    sudo systemctl start apparmor

- Verificar de novo.

===========================
6. Configurar SSH Seguro ✅
===========================
- Verificar se já está instalado:
    -» sudo systemctl status ssh

- Editar /etc/ssh/sshd_config:
*(Ctrl + w) Pesquisa
    Port 4242
    PermitRootLogin no
    AllowGroups sudo

- Reiniciar o SSH:
    sudo systemctl restart ssh

- Checar se está ouvindo na porta correta:
    sudo ss -tuln | grep 4242

===========================================
7. UFW – Firewall (Só porta 4242 aberta) ✅
===========================================
- Instalar UFW:
    sudo apt install ufw

- Liberar 4242/tcp:
    sudo ufw allow 4242/tcp

- Ativar firewall:
    sudo ufw enable

- Verificar status:
    sudo ufw status verbose

=============================
8. Política de Senha Forte ✅
=============================
- Verificar se já está instaldo
    apt list --installed | grep libpam-pwquality

- Instalar módulo de senha:
    sudo apt install libpam-pwquality

- Editar /etc/pam.d/common-password, linha:
    password requisite pam_pwquality.so retry=3 minlen=10 ucredit=-1 lcredit=-1 dcredit=-1 maxrepeat=3 reject_username difok=7

- Editar /etc/login.defs:
    PASS_MAX_DAYS   30
    PASS_MIN_DAYS   2
    PASS_WARN_AGE   7
    
- Aplicar política aos usuários:
    sudo chage --maxdays 30 --mindays 2 --warndays 7 seu_login
    sudo chage --maxdays 30 --mindays 2 --warndays 7 root

========================================
9. Sudoers Avançado (via sudo visudo) ✅
========================================
Adicione ao /etc/sudoers:
    Defaults    passwd_tries=3
    Defaults    badpass_message="Senha incorreta, tente novamente!"
    Defaults    logfile="/var/log/sudo/sudo.log"
    Defaults    log_input,log_output
    Defaults    requiretty
    Defaults    secure_path="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin"

- Criar pasta de logs:
    sudo mkdir -p /var/log/sudo
    sudo chmod 700 /var/log/sudo

========================================
Resumo dos Conceitos para Explicar na Banca
========================================
- VM: Isolamento, simulação real de servidor.
- LVM + LUKS: Flexibilidade e segurança dos dados.
- Hostname, grupos e sudo: Identidade, permissões, administração controlada.
- AppArmor: Protege o sistema contra comportamentos inesperados de programas.
- SSH e firewall: Acesso seguro e restrito à máquina.
- Política de senha forte/sudoers: Segurança contra ataques internos e externos.

========================================
O que falta após aqui?
========================================
- Script de monitoramento (monitoring.sh)
- Checklist e teste final
- Gerar assinatura do disco para entrega

========================================
Dicas extras:
========================================
- Mantenha esse checklist atualizado com anotações pessoais.
- Adicione detalhes de teclado, problemas encontrados e soluções para consultar fácil durante a banca.

========================================
