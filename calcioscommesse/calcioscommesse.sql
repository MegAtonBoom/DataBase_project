-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
-- -----------------------------------------------------
-- Schema calcioscommesse
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `calcioscommesse` ;

-- -----------------------------------------------------
-- Schema calcioscommesse
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `calcioscommesse` DEFAULT CHARACTER SET latin1 ;
USE `calcioscommesse` ;

-- -----------------------------------------------------
-- Table `calcioscommesse`.`arbitro`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `calcioscommesse`.`arbitro` ;

CREATE TABLE IF NOT EXISTS `calcioscommesse`.`arbitro` (
  `nome` VARCHAR(45) NOT NULL,
  `presenze` INT(11) NULL DEFAULT NULL,
  `paese` VARCHAR(30) NULL DEFAULT NULL,
  `citta` VARCHAR(45) NULL DEFAULT NULL,
  `via` VARCHAR(45) NULL DEFAULT NULL,
  `numero` INT(11) NULL DEFAULT NULL,
  PRIMARY KEY (`nome`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `calcioscommesse`.`cliente`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `calcioscommesse`.`cliente` ;

CREATE TABLE IF NOT EXISTS `calcioscommesse`.`cliente` (
  `cf` VARCHAR(16) NOT NULL,
  `nome` VARCHAR(45) NULL DEFAULT NULL,
  `cognome` VARCHAR(45) NULL DEFAULT NULL,
  `anno_nascita` INT(11) NULL DEFAULT NULL,
  `paese` VARCHAR(30) NULL DEFAULT NULL,
  `citta` VARCHAR(45) NULL DEFAULT NULL,
  `numero` INT(11) NULL DEFAULT NULL,
  `via` VARCHAR(45) NULL DEFAULT NULL,
  PRIMARY KEY (`cf`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `calcioscommesse`.`squadra`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `calcioscommesse`.`squadra` ;

CREATE TABLE IF NOT EXISTS `calcioscommesse`.`squadra` (
  `nome` VARCHAR(45) NOT NULL,
  `allenatore` VARCHAR(45) NULL DEFAULT NULL,
  PRIMARY KEY (`nome`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `calcioscommesse`.`edizione`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `calcioscommesse`.`edizione` ;

CREATE TABLE IF NOT EXISTS `calcioscommesse`.`edizione` (
  `anno` INT(11) NOT NULL,
  `squadra` VARCHAR(45) NULL DEFAULT NULL,
  PRIMARY KEY (`anno`),
  CONSTRAINT `edizione.squadra`
    FOREIGN KEY (`squadra`)
    REFERENCES `calcioscommesse`.`squadra` (`nome`)
    ON DELETE SET NULL
    ON UPDATE CASCADE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;

CREATE INDEX `edizione.squadra_idx` ON `calcioscommesse`.`edizione` (`squadra` ASC) VISIBLE;


-- -----------------------------------------------------
-- Table `calcioscommesse`.`giocatore`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `calcioscommesse`.`giocatore` ;

CREATE TABLE IF NOT EXISTS `calcioscommesse`.`giocatore` (
  `nome` VARCHAR(45) NOT NULL,
  `n_maglia` INT(11) NULL DEFAULT NULL,
  `paese` VARCHAR(30) NULL DEFAULT NULL,
  `citta` VARCHAR(45) NULL DEFAULT NULL,
  `via` VARCHAR(45) NULL DEFAULT NULL,
  `numero` INT(11) NULL DEFAULT NULL,
  `squadra` VARCHAR(45) NULL DEFAULT NULL,
  PRIMARY KEY (`nome`),
  CONSTRAINT `giocatore.squadra`
    FOREIGN KEY (`squadra`)
    REFERENCES `calcioscommesse`.`squadra` (`nome`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;

CREATE INDEX `giocatore.squadra_idx` ON `calcioscommesse`.`giocatore` (`squadra` ASC) VISIBLE;


-- -----------------------------------------------------
-- Table `calcioscommesse`.`turno`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `calcioscommesse`.`turno` ;

CREATE TABLE IF NOT EXISTS `calcioscommesse`.`turno` (
  `nome` VARCHAR(15) NOT NULL,
  PRIMARY KEY (`nome`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `calcioscommesse`.`partita`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `calcioscommesse`.`partita` ;

CREATE TABLE IF NOT EXISTS `calcioscommesse`.`partita` (
  `numero` INT(11) NOT NULL,
  `turno` VARCHAR(15) NOT NULL,
  `sq1` VARCHAR(45) NULL DEFAULT NULL,
  `sq2` VARCHAR(45) NULL DEFAULT NULL,
  `arbitro` VARCHAR(45) NULL DEFAULT NULL,
  `ora` TIMESTAMP NULL DEFAULT NULL,
  `citta` VARCHAR(45) NULL DEFAULT NULL,
  PRIMARY KEY (`turno`, `numero`),
  CONSTRAINT `partita.arbitro`
    FOREIGN KEY (`arbitro`)
    REFERENCES `calcioscommesse`.`arbitro` (`nome`)
    ON DELETE SET NULL
    ON UPDATE CASCADE,
  CONSTRAINT `partita.sq1`
    FOREIGN KEY (`sq1`)
    REFERENCES `calcioscommesse`.`squadra` (`nome`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `partita.sq2`
    FOREIGN KEY (`sq2`)
    REFERENCES `calcioscommesse`.`squadra` (`nome`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `partita.turno`
    FOREIGN KEY (`turno`)
    REFERENCES `calcioscommesse`.`turno` (`nome`)
    ON UPDATE CASCADE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;

CREATE INDEX `partita.sq1_idx` ON `calcioscommesse`.`partita` (`sq1` ASC) VISIBLE;

CREATE INDEX `partita.sq2_idx` ON `calcioscommesse`.`partita` (`sq2` ASC) VISIBLE;

CREATE INDEX `partita.arbitro_idx` ON `calcioscommesse`.`partita` (`arbitro` ASC) VISIBLE;

CREATE INDEX `partita.numero_idx` ON `calcioscommesse`.`partita` (`numero` ASC) VISIBLE;


-- -----------------------------------------------------
-- Table `calcioscommesse`.`goal`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `calcioscommesse`.`goal` ;

CREATE TABLE IF NOT EXISTS `calcioscommesse`.`goal` (
  `partita` INT(11) NOT NULL,
  `turno` VARCHAR(15) NOT NULL,
  `minuto` INT(11) NOT NULL,
  `rigore` TINYINT(4) NULL DEFAULT NULL,
  `giocatore` VARCHAR(45) NULL DEFAULT NULL,
  `min_recupero` INT(11) NOT NULL,
  PRIMARY KEY (`partita`, `turno`, `minuto`, `min_recupero`),
  CONSTRAINT `goal.giocatore`
    FOREIGN KEY (`giocatore`)
    REFERENCES `calcioscommesse`.`giocatore` (`nome`)
    ON DELETE SET NULL
    ON UPDATE CASCADE,
  CONSTRAINT `goal.partita`
    FOREIGN KEY (`partita` , `turno`)
    REFERENCES `calcioscommesse`.`partita` (`numero` , `turno`)
    ON UPDATE CASCADE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;

CREATE INDEX `goal.giocatore_idx` ON `calcioscommesse`.`goal` (`giocatore` ASC) VISIBLE;

CREATE INDEX `goal.turno_idx` ON `calcioscommesse`.`goal` (`turno` ASC) VISIBLE;

CREATE INDEX `goal.partita_idx` ON `calcioscommesse`.`goal` (`partita` ASC) VISIBLE;


-- -----------------------------------------------------
-- Table `calcioscommesse`.`partecipa`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `calcioscommesse`.`partecipa` ;

CREATE TABLE IF NOT EXISTS `calcioscommesse`.`partecipa` (
  `turno` VARCHAR(15) NOT NULL,
  `squadra` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`turno`, `squadra`),
  CONSTRAINT `partecipa.squadra`
    FOREIGN KEY (`squadra`)
    REFERENCES `calcioscommesse`.`squadra` (`nome`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `partecipa.turno`
    FOREIGN KEY (`turno`)
    REFERENCES `calcioscommesse`.`turno` (`nome`)
    ON UPDATE CASCADE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;

CREATE INDEX `partecipa.squadra_idx` ON `calcioscommesse`.`partecipa` (`squadra` ASC) VISIBLE;


-- -----------------------------------------------------
-- Table `calcioscommesse`.`scommessa`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `calcioscommesse`.`scommessa` ;

CREATE TABLE IF NOT EXISTS `calcioscommesse`.`scommessa` (
  `partita` INT(11) NOT NULL,
  `turno` VARCHAR(15) NOT NULL,
  `esito` INT(11) NOT NULL,
  `moltiplicatore` DOUBLE NOT NULL,
  PRIMARY KEY (`partita`, `turno`, `esito`),
  CONSTRAINT `scommessa.partita`
    FOREIGN KEY (`partita` , `turno`)
    REFERENCES `calcioscommesse`.`partita` (`numero` , `turno`)
    ON UPDATE CASCADE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;

CREATE INDEX `scommessa.esito_idx` ON `calcioscommesse`.`scommessa` (`esito` ASC) VISIBLE;


-- -----------------------------------------------------
-- Table `calcioscommesse`.`scommessa_reale`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `calcioscommesse`.`scommessa_reale` ;

CREATE TABLE IF NOT EXISTS `calcioscommesse`.`scommessa_reale` (
  `partita` INT(11) NOT NULL,
  `turno` VARCHAR(15) NOT NULL,
  `esito` INT(11) NOT NULL,
  `codice` VARCHAR(15) NOT NULL,
  `importo` DOUBLE NOT NULL,
  `cliente` VARCHAR(16) NOT NULL,
  PRIMARY KEY (`codice`),
  CONSTRAINT `scommessa_reale.cliente`
    FOREIGN KEY (`cliente`)
    REFERENCES `calcioscommesse`.`cliente` (`cf`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `scommessa_reale.partita`
    FOREIGN KEY (`esito` , `partita` , `turno`)
    REFERENCES `calcioscommesse`.`scommessa` (`esito` , `partita` , `turno`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;

CREATE INDEX `scommessa_reale.cliente_idx` ON `calcioscommesse`.`scommessa_reale` (`cliente` ASC) VISIBLE;

CREATE INDEX `scommessa_reale.esito_idx` ON `calcioscommesse`.`scommessa_reale` (`esito` ASC, `partita` ASC, `turno` ASC) VISIBLE;


-- -----------------------------------------------------
-- Table `calcioscommesse`.`utente`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `calcioscommesse`.`utente` ;

CREATE TABLE IF NOT EXISTS `calcioscommesse`.`utente` (
  `nome` VARCHAR(45) NULL DEFAULT NULL,
  `cognome` VARCHAR(45) NULL DEFAULT NULL,
  `username` VARCHAR(45) NOT NULL,
  `password` VARCHAR(45) NOT NULL,
  `ruolo` ENUM('amministratore', 'addetto_sportelli') NOT NULL,
  PRIMARY KEY (`username`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;

USE `calcioscommesse` ;

-- -----------------------------------------------------
-- procedure aggiorna_tornero
-- -----------------------------------------------------

USE `calcioscommesse`;
DROP procedure IF EXISTS `calcioscommesse`.`aggiorna_tornero`;

DELIMITER $$
USE `calcioscommesse`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `aggiorna_tornero`(in turnosucc varchar(15))
BEGIN
	declare counter1, counter2, counterp int;
    declare ultima_partita timestamp;
    declare squadra1, squadra2 varchar(45);
    declare turnoprec varchar(15);
    
    declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;
    
    if turnosucc="quarti" then 
		set turnoprec = "ottavi"; 
        set counterp = 8;
    end if;
    
    if turnosucc="semifinale" then 
		set turnoprec = "quarti";
        set counterp = 4;
    end if;
    
    if turnosucc="finale" then 
		set turnoprec = "semifinale"; 
        set counterp = 2;
    end if;
    
    
    
    set transaction isolation level serializable;
    start transaction;
    
    select count(*) from partecipa where turno=turnosucc into counter1;
    if counter1!=0 then
		signal sqlstate '45001' set message_text = "Squadre del turno successivo gia calcolate!";
	end if;
    
    select max(ora) from partita where turno = turnoprec into ultima_partita;
    if ultima_partita > (NOW() - interval 3 hour) then	
		signal sqlstate '45002' set message_text = "Non sono ancora state giocate tutte le partite!";
	end if;
    
    select count(*) from partita where turno = turnoprec into counter1;
    if counter1!=counterp then
		signal sqlstate '45003' set message_text = "Non c'è un numero di partite sufficiente per determinare il prossimo turno!";
    end if;
 
    begin
            
				 #squadre per ciascuna partita
				 declare done int default false;
				 declare cur cursor for select sq1, sq2
				 from `partita`  
				 where turno = turnoprec;
				 
				 declare continue handler for not found set done = true;
			
			open cur;
            contagoal: loop
				fetch cur into squadra1, squadra2;
                
                if done then
					leave contagoal;
				end if;
                
                #goal squadra1
                select count(*) 
                from partita join goal on goal.partita=partita.numero and goal.turno=partita.turno
                join giocatore on goal.giocatore=giocatore.nome
                where giocatore.squadra=squadra1  into counter1;
                
                #goal squadra2
                select count(*) 
                from partita join goal on goal.partita=partita.numero and goal.turno=partita.turno
                join giocatore on goal.giocatore=giocatore.nome
                where giocatore.squadra=squadra2  into counter2;
                
                if counter1=counter2 then
					signal sqlstate '45000' set message_text = "La partita non può essere finita in parita! Aggiornamento goal richiesto!";
				end if;
                
                #inserisci squadra vincitrice nel turno successivo
                if counter1 > counter2 then
					INSERT INTO partecipa(turno, squadra) VALUES (turnosucc, squadra1);
				else
					INSERT INTO partecipa(turno, squadra) VALUES (turnosucc, squadra2);
				end if;
                
                
            end loop;
            close cur;
	end;
	commit;
    
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_arbitro
-- -----------------------------------------------------

USE `calcioscommesse`;
DROP procedure IF EXISTS `calcioscommesse`.`aggiungi_arbitro`;

DELIMITER $$
USE `calcioscommesse`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `aggiungi_arbitro`(in v_nome varchar(45), in v_pres int, in v_paese varchar(30), in v_citta varchar(45), in v_via varchar(45), in v_num int)
BEGIN
	insert into arbitro values (v_nome, v_pres, v_paese, v_citta, v_via, v_num);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_cliente
-- -----------------------------------------------------

USE `calcioscommesse`;
DROP procedure IF EXISTS `calcioscommesse`.`aggiungi_cliente`;

DELIMITER $$
USE `calcioscommesse`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `aggiungi_cliente`(IN v_cf varchar(16), IN v_nome varchar(45), IN v_cognome varchar(45), IN v_anno INT, IN v_paese varchar(30), IN v_citta varchar(45), IN v_via varchar(45), IN v_num INT)
BEGIN
	insert into cliente values(v_cf, v_nome, v_cognome, v_anno, v_paese, v_citta, v_num, v_via);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_giocatore
-- -----------------------------------------------------

USE `calcioscommesse`;
DROP procedure IF EXISTS `calcioscommesse`.`aggiungi_giocatore`;

DELIMITER $$
USE `calcioscommesse`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `aggiungi_giocatore`(in v_nome varchar(45), in v_maglia int, in v_paese varchar(30), in v_citta varchar(45), in v_via varchar(45), in v_numero int, in v_squadra varchar(45) )
BEGIN
	
    insert into giocatore values ( v_nome, v_maglia, v_paese, v_citta, v_via, v_numero, v_squadra);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_goal
-- -----------------------------------------------------

USE `calcioscommesse`;
DROP procedure IF EXISTS `calcioscommesse`.`aggiungi_goal`;

DELIMITER $$
USE `calcioscommesse`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `aggiungi_goal`(in v_partita int, in v_turno varchar(15), in v_minuto int, in  v_rigore tinyint, in v_giocatore varchar(45), in v_min_recupero int)
BEGIN

	insert into goal values(v_partita, v_turno, v_minuto, v_rigore, v_giocatore, v_min_recupero);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_partecipazione
-- -----------------------------------------------------

USE `calcioscommesse`;
DROP procedure IF EXISTS `calcioscommesse`.`aggiungi_partecipazione`;

DELIMITER $$
USE `calcioscommesse`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `aggiungi_partecipazione`(in v_turno varchar(15), in v_squadra varchar(45))
BEGIN
	insert into partecipa values(v_turno, v_squadra);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_partita_e_scommesse
-- -----------------------------------------------------

USE `calcioscommesse`;
DROP procedure IF EXISTS `calcioscommesse`.`aggiungi_partita_e_scommesse`;

DELIMITER $$
USE `calcioscommesse`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `aggiungi_partita_e_scommesse`(IN v_num int, IN v_turno varchar(15), in v_sq1 varchar(45), in v_sq2 varchar(45), IN v_arbitro varchar(45), IN v_orario timestamp, IN v_citta varchar(45), IN v_molt1 double, IN v_molt2 double, IN v_moltpar double)
BEGIN

	declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;
    
    set transaction isolation level read committed;
    start transaction;
	
		insert into partita values(v_num, v_turno, v_sq1, v_sq2, v_arbitro, v_orario, v_citta);
		if v_turno="qualificazione" then
			insert into scommessa values (v_num, v_turno, 0, v_moltpar);
		end if;
		insert into scommessa values (v_num, v_turno, 1, v_molt1);
		insert into scommessa values (v_num, v_turno, 2, v_molt2);
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_scommessa_cliente
-- -----------------------------------------------------

USE `calcioscommesse`;
DROP procedure IF EXISTS `calcioscommesse`.`aggiungi_scommessa_cliente`;

DELIMITER $$
USE `calcioscommesse`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `aggiungi_scommessa_cliente`(IN v_partita int, IN v_turno varchar(15), IN v_esito int, IN v_codice varchar(15), IN v_importo double, IN v_cliente varchar(16))
BEGIN
	insert into scommessa_reale values (v_partita, v_turno, v_esito, v_codice, v_importo, v_cliente);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_squadra
-- -----------------------------------------------------

USE `calcioscommesse`;
DROP procedure IF EXISTS `calcioscommesse`.`aggiungi_squadra`;

DELIMITER $$
USE `calcioscommesse`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `aggiungi_squadra`(in v_nome varchar(45), in v_allenatore varchar(45))
BEGIN
	insert into squadra values (v_nome, v_allenatore);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_utente
-- -----------------------------------------------------

USE `calcioscommesse`;
DROP procedure IF EXISTS `calcioscommesse`.`aggiungi_utente`;

DELIMITER $$
USE `calcioscommesse`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `aggiungi_utente`(in v_nome varchar(45), in v_cognome varchar(45), in v_username varchar(45), in v_pass varchar(45), in v_ruolo varchar(45))
BEGIN
	insert into utente values( v_nome, v_cognome, v_username, MD5(v_pass), v_ruolo);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure login_utente
-- -----------------------------------------------------

USE `calcioscommesse`;
DROP procedure IF EXISTS `calcioscommesse`.`login_utente`;

DELIMITER $$
USE `calcioscommesse`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `login_utente`(in v_username varchar(45), in v_pass varchar(45), out v_ruolo INT)
BEGIN
	declare var_user_role ENUM('amministratore', 'addetto_sportelli');
    
	select ruolo from utente
		where username = v_username
        and password = md5(v_pass)
        into var_user_role;
        
        -- See the corresponding enum in the client
		if var_user_role = 'amministratore' then
			set v_ruolo = 1;
		elseif var_user_role = 'addetto_sportelli' then
			set v_ruolo = 2;
		else
			set v_ruolo = 3;
		end if;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure modifica_cliente
-- -----------------------------------------------------

USE `calcioscommesse`;
DROP procedure IF EXISTS `calcioscommesse`.`modifica_cliente`;

DELIMITER $$
USE `calcioscommesse`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `modifica_cliente`(IN v_cf varchar(16), IN v_nome varchar(45), IN v_cognome varchar(45), IN v_anno INT, IN v_paese varchar(30), IN v_citta varchar(45), IN v_via varchar(45), IN v_num INT)
BEGIN
	update cliente 
    set nome=v_nome,
    cognome=v_cognome,
    anno_nascita=v_anno, 
    paese=v_paese,
    citta=v_citta,
    via=v_via,
    numero=v_num
    where cf=v_cf;
    
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure trova_capocannoniere
-- -----------------------------------------------------

USE `calcioscommesse`;
DROP procedure IF EXISTS `calcioscommesse`.`trova_capocannoniere`;

DELIMITER $$
USE `calcioscommesse`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `trova_capocannoniere`()
BEGIN

	declare countg int;
    declare cgiocatore varchar(45);
	declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;
    
    set transaction isolation level read committed;
    start transaction;

		select count(*), giocatore 
        from goal as g
        group by g.giocatore
        having count(*) = (
							select count(*) as conta
                            from goal
                            where giocatore = g.giocatore
                            group by giocatore
                            order by conta desc)
		limit 1 into countg, cgiocatore;
        
        select countg as numero_goal;
        select nome, n_maglia, squadra from giocatore where nome = cgiocatore;

	commit;
		
    
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure trova_cliente_ricco
-- -----------------------------------------------------

USE `calcioscommesse`;
DROP procedure IF EXISTS `calcioscommesse`.`trova_cliente_ricco`;

DELIMITER $$
USE `calcioscommesse`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `trova_cliente_ricco`()
BEGIN
	declare n_cliente varchar(16);
    declare importoc double;
	declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;
    
    set transaction isolation level serializable;
    start transaction;
		select sc.cliente as cliente, sc.importo as importo 
        from scommessa_reale as sc 
        join partita as p on sc.partita=p.numero and sc.turno=p.turno
        join cliente as c on sc.cliente=c.cf
        having sc.importo = (
							select max(importo) 
                            from scommessa_reale
                            ) into n_cliente, importoc; 
                            
                            
		select c.nome as nome, c.cognome as cognome, c.paese as paese, sr.importo as importo_scommessa, 
        p.turno as turno, p.sq1 as squadra_1, p.sq2 as squadra_2, sr.esito as esito_scommesso
        from scommessa_reale as sr
        join cliente as c on c.cf=sr.cliente
        join partita as p on p.numero=sr.partita and p.turno=sr.turno
        where c.cf=n_cliente;
   
    
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure trova_moltiplicatore_maggiore
-- -----------------------------------------------------

USE `calcioscommesse`;
DROP procedure IF EXISTS `calcioscommesse`.`trova_moltiplicatore_maggiore`;

DELIMITER $$
USE `calcioscommesse`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `trova_moltiplicatore_maggiore`()
BEGIN
	select p.sq1 as squadra1, p.sq2 as squadra2, p.turno as turno, s.esito as esito, s.moltiplicatore as molitiplicatore 
    from scommessa as s join partita as p on s.partita=p.numero and s.turno=p.turno
    where s.moltiplicatore = (
								select max(moltiplicatore)
                                from scommessa);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure trova_partita_piu_scommessa
-- -----------------------------------------------------

USE `calcioscommesse`;
DROP procedure IF EXISTS `calcioscommesse`.`trova_partita_piu_scommessa`;

DELIMITER $$
USE `calcioscommesse`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `trova_partita_piu_scommessa`()
BEGIN
	declare v_numero, v_partita int;
    declare v_turno varchar(15);
    
    declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;
    
    set transaction isolation level read committed;
    start transaction;
    
		select count(*), partita, turno 
		from scommessa_reale 
		group by partita, turno 
		order by count(*) desc 
		limit 1  into v_numero, v_partita, v_turno;
		
        select v_numero as bet_number;
        
		select * from partita where numero=v_partita and turno=v_turno;
        
	commit;
    
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure trova_partite_future
-- -----------------------------------------------------

USE `calcioscommesse`;
DROP procedure IF EXISTS `calcioscommesse`.`trova_partite_future`;

DELIMITER $$
USE `calcioscommesse`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `trova_partite_future`()
BEGIN
	select * 
    from partita
    where ((ora + interval 3 hour) - NOW() )>0;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure trova_piu_goal
-- -----------------------------------------------------

USE `calcioscommesse`;
DROP procedure IF EXISTS `calcioscommesse`.`trova_piu_goal`;

DELIMITER $$
USE `calcioscommesse`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `trova_piu_goal`()
BEGIN

    
	declare v_goal, v_partita int;
    declare v_turno varchar(15);
    
    declare exit handler for sqlexception
	begin
			rollback;  -- rollback any changes made in the transaction
			resignal;  -- raise again the sql exception to the caller
	end;
    
    set transaction isolation level read committed;
    start transaction;

	select count(*),partita, turno
    from goal
    group by partita, turno
    order by count(*) desc
    limit 1 into v_goal, v_partita, v_turno;
    
    select v_goal as goal_number;
    
    select * from partita where numero=v_partita and turno=v_turno;
    
    commit;
    
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure trova_presenze_arbitro
-- -----------------------------------------------------

USE `calcioscommesse`;
DROP procedure IF EXISTS `calcioscommesse`.`trova_presenze_arbitro`;

DELIMITER $$
USE `calcioscommesse`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `trova_presenze_arbitro`(in v_nome varchar(45))
BEGIN
	select presenze from arbitro where nome=v_nome;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure trova_sq_per_turno
-- -----------------------------------------------------

USE `calcioscommesse`;
DROP procedure IF EXISTS `calcioscommesse`.`trova_sq_per_turno`;

DELIMITER $$
USE `calcioscommesse`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `trova_sq_per_turno`(in v_turno varchar(15))
BEGIN	
		select nome as squadre 
        from partecipa as p join squadra as s on p.squadra = s.nome
        where p.turno = v_turno;
END$$

DELIMITER ;
USE `calcioscommesse`;

DELIMITER $$

USE `calcioscommesse`$$
DROP TRIGGER IF EXISTS `calcioscommesse`.`arbitro_BEFORE_INSERT` $$
USE `calcioscommesse`$$
CREATE
DEFINER=`root`@`localhost`
TRIGGER `calcioscommesse`.`arbitro_BEFORE_INSERT`
BEFORE INSERT ON `calcioscommesse`.`arbitro`
FOR EACH ROW
BEGIN
	if NEW.numero < 0 or NEW.presenze < 0 then
			signal sqlstate '45000';
	end if;
END$$


USE `calcioscommesse`$$
DROP TRIGGER IF EXISTS `calcioscommesse`.`cliente_BEFORE_INSERT` $$
USE `calcioscommesse`$$
CREATE
DEFINER=`root`@`localhost`
TRIGGER `calcioscommesse`.`cliente_BEFORE_INSERT`
BEFORE INSERT ON `calcioscommesse`.`cliente`
FOR EACH ROW
BEGIN
	if NEW.numero < 0 then
			signal sqlstate '45000';
	end if;
    if NEW.anno_nascita < 1900 or NEW.anno_nascita > 2003 then
			signal sqlstate '45000';
	end if;
END$$


USE `calcioscommesse`$$
DROP TRIGGER IF EXISTS `calcioscommesse`.`cliente_BEFORE_UPDATE` $$
USE `calcioscommesse`$$
CREATE
DEFINER=`root`@`localhost`
TRIGGER `calcioscommesse`.`cliente_BEFORE_UPDATE`
BEFORE UPDATE ON `calcioscommesse`.`cliente`
FOR EACH ROW
BEGIN
	if NEW.numero < 0 then
			signal sqlstate '45000';
	end if;
    if NEW.anno_nascita < 1900 or NEW.anno_nascita > 2003 then
			signal sqlstate '45000';
	end if;
END$$


USE `calcioscommesse`$$
DROP TRIGGER IF EXISTS `calcioscommesse`.`edizione_BEFORE_INSERT` $$
USE `calcioscommesse`$$
CREATE
DEFINER=`root`@`localhost`
TRIGGER `calcioscommesse`.`edizione_BEFORE_INSERT`
BEFORE INSERT ON `calcioscommesse`.`edizione`
FOR EACH ROW
BEGIN
	if NEW.anno = 1942 or NEW.anno = 1946 or NEW.anno < 1930 then
			signal sqlstate '45000';
	end if;
    if ((NEW.anno - 1930)%4) != 0 then
			signal sqlstate '45000';
	end if;
END$$


USE `calcioscommesse`$$
DROP TRIGGER IF EXISTS `calcioscommesse`.`giocatore_BEFORE_INSERT` $$
USE `calcioscommesse`$$
CREATE
DEFINER=`root`@`localhost`
TRIGGER `calcioscommesse`.`giocatore_BEFORE_INSERT`
BEFORE INSERT ON `calcioscommesse`.`giocatore`
FOR EACH ROW
BEGIN
	declare counter INT;
	if NEW.n_maglia < 0 or NEW.n_maglia > 99 then
			signal sqlstate '45000';
	end if;
    if NEW.numero < 0 then
			signal sqlstate '45000';
	end if;
	select count(*) from giocatore where squadra=NEW.squadra and n_maglia=NEW.n_maglia into counter;
	if counter>0 then
		signal sqlstate '45000';
	end if;

END$$


USE `calcioscommesse`$$
DROP TRIGGER IF EXISTS `calcioscommesse`.`turno_BEFORE_INSERT` $$
USE `calcioscommesse`$$
CREATE
DEFINER=`root`@`localhost`
TRIGGER `calcioscommesse`.`turno_BEFORE_INSERT`
BEFORE INSERT ON `calcioscommesse`.`turno`
FOR EACH ROW
BEGIN
	declare c1,c2,c3,c4,c5 INT;
    select strcmp(NEW.nome, "qualificazione") into c1;
    select strcmp(NEW.nome, "ottavi") into c2;
    select strcmp(NEW.nome, "quarti") into c3;
    select strcmp(NEW.nome, "semifinale") into c4;
    select strcmp(NEW.nome, "finale") into c5;
	if c1!=0 and c2!=0 and c3!=0 and c4!=0 and c5!=0 then 
		signal sqlstate '45000';
	end if;
END$$


USE `calcioscommesse`$$
DROP TRIGGER IF EXISTS `calcioscommesse`.`partita_BEFORE_INSERT` $$
USE `calcioscommesse`$$
CREATE
DEFINER=`root`@`localhost`
TRIGGER `calcioscommesse`.`partita_BEFORE_INSERT`
BEFORE INSERT ON `calcioscommesse`.`partita`
FOR EACH ROW
BEGIN
	declare counter1, counter2 INT;
    declare turnoprec varchar(15);
    declare matcht1, matcht2 timestamp;
    if NEW.turno != "qualificazione" then
		select count(*) from partita where turno = NEW.turno and (sq1 = NEW.sq1 or sq2 = NEW.sq1) into counter1;
		select count(*) from partita where turno = NEW.turno and (sq1 = NEW.sq2 or sq2 = NEW.sq2) into counter2;
		if counter1 != 0 or counter2 != 0 then
				signal sqlstate '45000' SET MESSAGE_TEXT = 'Una delle squadre partecipa gia a una partita!';
		end if;
	end if;
    select count(*) from partecipa where squadra=NEW.sq1 and turno=NEW.turno into counter1;
    select count(*) from partecipa where squadra=NEW.sq2 and turno=NEW.turno into counter2;
    
    if counter1 = 0 or counter2 = 0 then
		signal sqlstate '45000' SET MESSAGE_TEXT = 'Le squadre non partecipano a questo turno!';
	end if;
    
    if NEW.sq1=NEW.sq2 then
		signal sqlstate '45000' SET MESSAGE_TEXT = 'Non puo partecipare solo una squadra alla partita!';
	end if;
    
	if(NEW.turno="quarti") then
		set turnoprec="ottavi";
    elseif(NEW.turno="semifinale") then
		set turnoprec="quarti";
    elseif(NEW.turno="finale") then
		set turnoprec="semifinale";
	end if;
    
    select ora 
    from partita 
    where sq1=NEW.sq1 or sq2=NEW.sq1 and turno=turnoprec 
    into matcht1;
    
    select ora 
    from partita 
    where sq1=NEW.sq2 or sq2=NEW.sq2 and turno=turnoprec 
    into matcht2;
    
    if((NEW.ora-matcht1)<0 or (NEW.ora-matcht2)<0) then
		signal sqlstate '45000' SET MESSAGE_TEXT = 'Partite non ordinate correttamente!';
	end if;
    
    update arbitro set presenze=presenze+1 where nome=NEW.arbitro;
END$$


USE `calcioscommesse`$$
DROP TRIGGER IF EXISTS `calcioscommesse`.`goal_BEFORE_INSERT` $$
USE `calcioscommesse`$$
CREATE
DEFINER=`root`@`localhost`
TRIGGER `calcioscommesse`.`goal_BEFORE_INSERT`
BEFORE INSERT ON `calcioscommesse`.`goal`
FOR EACH ROW
BEGIN
	declare squadra1, squadra2, sqgiocatore varchar(45);
    declare matcht timestamp;
	if NEW.minuto<1 or NEW.min_recupero<0  then
			signal sqlstate '45000' SET MESSAGE_TEXT = 'Valore minuti non valido!';
	end if;
    
    select sq1,sq2 from partita where numero=NEW.partita and turno=NEW.turno into squadra1,squadra2;
    select squadra from giocatore where nome=NEW.giocatore into sqgiocatore;
    select ora from partita where numero=NEW.partita and turno=NEW.turno into matcht;
    
    if sqgiocatore != squadra1 and sqgiocatore != squadra2 then
		signal sqlstate '45000' SET MESSAGE_TEXT = 'Il giocatore non appartiene ad una delle squadre che si sono affrontate!';
	end if;
    
    if (NEW.minuto!=45 and NEW.minuto!=90 and NEW.minuto!=105 and NEW.minuto!=120) and NEW.min_recupero !=0 then
		signal sqlstate '45000' SET MESSAGE_TEXT = 'Minuto di recupero non valido!';
	end if;
    
    if NEW.minuto>120 and NEW.rigore=0 then
		signal sqlstate '45000' SET MESSAGE_TEXT = 'Durante la fase a rigori, solo i rigori sono ammessi!';
	end if;
    
    if NEW.rigore!=0 and NEW.rigore!=1 then
		signal sqlstate '45000' SET MESSAGE_TEXT = 'Valore attributo rigore sbagliato!';
	end if;
    
    if (matcht-NOW())>0 then
		signal sqlstate '45000' SET MESSAGE_TEXT = 'La partita non e stata ancora giocata!';
	end if;
      
	if(NEW.turno="qualificazione" and NEW.minuto>90) then
		signal sqlstate '45000' SET MESSAGE_TEXT = "In questa fase non ci sono i tempi supplementari!";
	end if;
	
        
END$$


USE `calcioscommesse`$$
DROP TRIGGER IF EXISTS `calcioscommesse`.`partecipa_BEFORE_INSERT` $$
USE `calcioscommesse`$$
CREATE
DEFINER=`root`@`localhost`
TRIGGER `calcioscommesse`.`partecipa_BEFORE_INSERT`
BEFORE INSERT ON `calcioscommesse`.`partecipa`
FOR EACH ROW
BEGIN
	declare counter INT;
    if NEW.turno = "qualificazione" then
		select count(*) from partecipa where turno="qualificazione" into counter;
        if counter > 31 then
			signal sqlstate '45000' SET MESSAGE_TEXT = 'Numero squadre non congruo alle regole del calcio!';
		end if;	
    elseif NEW.turno = "ottavi" then
		select count(*) from partecipa where turno="ottavi" into counter;
        if counter > 15 then
			signal sqlstate '45000'SET MESSAGE_TEXT = 'Numero squadre per questo turno non congruo alle regole del calcio!';
		end if;	
    elseif NEW.turno = "quarti" then
		select count(*) from partecipa where turno="quarti" into counter;
        if counter > 7 then
			signal sqlstate '45000'SET MESSAGE_TEXT = 'Numero squadre per questo turno non congruo alle regole del calcio!';
		end if;
	elseif NEW.turno = "semifinale" then
		select count(*) from partecipa where turno="semifinale" into counter;
        if counter > 3 then
			signal sqlstate '45000'SET MESSAGE_TEXT = 'Numero squadre per questo turno non congruo alle regole del calcio!';
		end if;
	elseif NEW.turno = "finale" then
		select count(*) from partecipa where turno="finale" into counter;
        if counter > 1 then
			signal sqlstate '45000'SET MESSAGE_TEXT = 'Numero squadre per questo turno non congruo alle regole del calcio!';
		end if;
	end if;

END$$


USE `calcioscommesse`$$
DROP TRIGGER IF EXISTS `calcioscommesse`.`scommessa_BEFORE_INSERT` $$
USE `calcioscommesse`$$
CREATE
DEFINER=`root`@`localhost`
TRIGGER `calcioscommesse`.`scommessa_BEFORE_INSERT`
BEFORE INSERT ON `calcioscommesse`.`scommessa`
FOR EACH ROW
BEGIN
	if NEW.esito < 0 or NEW.esito > 2 then
			signal sqlstate '45000'SET MESSAGE_TEXT = 'Esito non valido!';
	end if;
    if NEW.esito = 0 and NEW.turno != "qualificazione" then
			signal sqlstate '45000' SET MESSAGE_TEXT = 'Non si puo pareggiare dopo le qualificazioni!';
	end if;
    if NEW.moltiplicatore<1 then
			signal sqlstate '45000' SET MESSAGE_TEXT = 'Non si puo avere un moltiplicatore <1!';
	end if;
    
END$$


USE `calcioscommesse`$$
DROP TRIGGER IF EXISTS `calcioscommesse`.`scommessa_reale_BEFORE_INSERT` $$
USE `calcioscommesse`$$
CREATE
DEFINER=`root`@`localhost`
TRIGGER `calcioscommesse`.`scommessa_reale_BEFORE_INSERT`
BEFORE INSERT ON `calcioscommesse`.`scommessa_reale`
FOR EACH ROW
BEGIN
	declare orariop TIMESTAMP;
	if NEW.importo < 0 then
			signal sqlstate '45000' set message_text = "Non si puo scommettere un importo negativo!";
	end if;
    select ora from partita where numero=NEW.partita and turno=NEW.turno into orariop;
    if orariop - NOW() < 0 then
			signal sqlstate '45000' set message_text = "Non si puo scommettere su una partita gia giocata!";
	end if;

END$$


DELIMITER ;
SET SQL_MODE = '';
DROP USER IF EXISTS login;
SET SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';
CREATE USER 'login' IDENTIFIED BY 'login';

GRANT EXECUTE ON procedure `calcioscommesse`.`login_utente` TO 'login';
SET SQL_MODE = '';
DROP USER IF EXISTS amministratore;
SET SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';
CREATE USER 'amministratore' IDENTIFIED BY 'amministratore';

GRANT EXECUTE ON procedure `calcioscommesse`.`aggiorna_tornero` TO 'amministratore';
GRANT EXECUTE ON procedure `calcioscommesse`.`aggiungi_arbitro` TO 'amministratore';
GRANT EXECUTE ON procedure `calcioscommesse`.`aggiungi_giocatore` TO 'amministratore';
GRANT EXECUTE ON procedure `calcioscommesse`.`aggiungi_goal` TO 'amministratore';
GRANT EXECUTE ON procedure `calcioscommesse`.`aggiungi_partita_e_scommesse` TO 'amministratore';
GRANT EXECUTE ON procedure `calcioscommesse`.`aggiungi_squadra` TO 'amministratore';
GRANT EXECUTE ON procedure `calcioscommesse`.`aggiungi_partecipazione` TO 'amministratore';
GRANT EXECUTE ON procedure `calcioscommesse`.`aggiungi_utente` TO 'amministratore';
SET SQL_MODE = '';
DROP USER IF EXISTS addetto_sportelli;
SET SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';
CREATE USER 'addetto_sportelli' IDENTIFIED BY 'addetto_sportelli';

GRANT EXECUTE ON procedure `calcioscommesse`.`aggiungi_cliente` TO 'addetto_sportelli';
GRANT EXECUTE ON procedure `calcioscommesse`.`modifica_cliente` TO 'addetto_sportelli';
GRANT EXECUTE ON procedure `calcioscommesse`.`aggiungi_scommessa_cliente` TO 'addetto_sportelli';
GRANT EXECUTE ON procedure `calcioscommesse`.`trova_moltiplicatore_maggiore` TO 'addetto_sportelli';
GRANT EXECUTE ON procedure `calcioscommesse`.`trova_partite_future` TO 'addetto_sportelli';
GRANT EXECUTE ON procedure `calcioscommesse`.`trova_partita_piu_scommessa` TO 'addetto_sportelli';
GRANT EXECUTE ON procedure `calcioscommesse`.`trova_sq_per_turno` TO 'addetto_sportelli';
GRANT EXECUTE ON procedure `calcioscommesse`.`trova_capocannoniere` TO 'addetto_sportelli';
GRANT EXECUTE ON procedure `calcioscommesse`.`trova_cliente_ricco` TO 'addetto_sportelli';
GRANT EXECUTE ON procedure `calcioscommesse`.`trova_piu_goal` TO 'addetto_sportelli';
GRANT EXECUTE ON procedure `calcioscommesse`.`trova_presenze_arbitro` TO 'addetto_sportelli';

SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;

-- -----------------------------------------------------
-- Data for table `calcioscommesse`.`turno`
-- -----------------------------------------------------
START TRANSACTION;
USE `calcioscommesse`;
INSERT INTO `calcioscommesse`.`turno` (`nome`) VALUES ('qualificazione');
INSERT INTO `calcioscommesse`.`turno` (`nome`) VALUES ('ottavi');
INSERT INTO `calcioscommesse`.`turno` (`nome`) VALUES ('quarti');
INSERT INTO `calcioscommesse`.`turno` (`nome`) VALUES ('semifinale');
INSERT INTO `calcioscommesse`.`turno` (`nome`) VALUES ('finale');

COMMIT;
