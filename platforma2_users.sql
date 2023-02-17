-- MySQL dump 10.13  Distrib 8.0.30, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: platforma2
-- ------------------------------------------------------
-- Server version	8.0.30

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `users` (
  `id_user` int NOT NULL AUTO_INCREMENT,
  `nume` varchar(45) DEFAULT NULL,
  `prenume` varchar(45) DEFAULT NULL,
  `cnp` varchar(45) DEFAULT NULL,
  `adresa` varchar(45) DEFAULT NULL,
  `telefon` varchar(45) DEFAULT NULL,
  `email` varchar(45) DEFAULT NULL,
  `iban` varchar(45) DEFAULT NULL,
  `nr_contract` varchar(45) DEFAULT NULL,
  `parola` varchar(45) DEFAULT NULL,
  `rol` varchar(45) NOT NULL,
  PRIMARY KEY (`id_user`)
) ENGINE=InnoDB AUTO_INCREMENT=91 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'Almond','Angela','5039493659','Strada Lalelelor nr.23','0721245646','almondangela@student.com','RO75857463','1','alan','student'),(2,'Bachert','Blake','5008885855','Strada Misunilor nr.22','0741659324','bachertblake@student.com','RO7895315','2','babl','student'),(3,'Binns','Diana','5039123479','Strada Lacuri nr.67','0724631914','binnsdiana@student.com','RO789542319','3','bidi','student'),(4,'Badera','David','5031223659','Strada Florii nr.354','0763649165','baderadavid@student.com','RO48623184','4','bada','student'),(5,'Carr','Ileana','5031658659','Strada Caselor nr.20','0756349814','carrileana@student.com','RO285761586','5','cail','student'),(6,'Cornell','Matthew','5029413325','Strada Ioan Budai nr.85','0766315428','cornellmatthew@student.com','RO12376544','6','coma','student'),(7,'Dumm','George','5029789659','Strada Cosmat nr.51','0789431622','dummgeorge@student.com','RO7895146','7','duge','student'),(8,'Dinimescu','Andrei','5029493665','Strada Dunarilor nr.88','0766345127','dinimescuandrei@student.com','RO4586271','33','dian','student'),(9,'Elecfi','Sergiu','5029478942','Strada Strazilor nr.1','0769693136','Monkeyz@student.com','RO63247519','54','else','student'),(10,'Chirtes','Lisandra','502949322','Strada Targului nr.11','0745420152','chirteslisandra@student.com','RO138246848','12','chli','student'),(11,'Huza','Adelina','5025657439','Strada Muresului nr.15','0785496523','huzaadelina@student.com','RO758294234','34','huad','student'),(12,'Boar','Dani','5029455679','Strada Misunilor nr.23','0745896321','boardani@student.com','RO47894225','45','boda','student'),(13,'Boar','Taylor','5019445679','Strada Allen nr.46','0741236589','boartaylor@student.com','RO4564123687','33','bota','student'),(14,'Groman','Mihai','5019448969','Strada Mare nr.1566','0712368549','gromanmihai@student.com','RO46468732','45','grmi','student'),(15,'Dumpty','Humpty','5015565679','Strada Cartilor nr.413','0745689123','H_D@student.com','RO786452348','45','duhu','student'),(16,'Bolcan','Cassandra','5013326679','Strada Eminescului nr.89','0763289412','bolcancassandra@student.com','RO4365418','345','boca','student'),(18,'Jineam','Vasile','5019445888','Strada Muzeului nr.22','0745213698','jnimeanvasile@student.com','RO1533874152','12','jiva','student'),(19,'Jolt','Spencer','5049415378','Strada Gineamului nr.903','0723659841','joltspencer@student.com','RO12387385','102','josp','student'),(20,'Kopp','Lukas','5049415658','Strada Popii nr.11','0745216398','kopplukas@student.com','RO13286353','54','kolu','student'),(21,'Lemington','Fram','5044565378','Strada Geamului nr.106','0745236981','lemingtonfram@student.com','RO486534156','234','lefr','student'),(22,'Sponge','Bob','5046657278','Strada Ananasului nr.212','0765329841','Bob@C_P.com','RO443542345','321','spobo','student'),(23,'Isman','Marcel','5049411212','Strada Ichban nr.182','0756328914','ismanmarcel@student.com','RO4545384835','7','isma','student'),(24,'Pojar','Andrews','5039411212','Strada Dunarilor nr.1000','0756984123','pojarandrews@student.com','RO15343545','489','poan','student'),(25,'Weppon','Akdemic','5039884212','Strada Baritiu nr.27','0723689451','wepponakdemic@student.com','RO786453415','489','weak','student'),(26,'Kerr','Sophia','5039411211','Strada Misunilor nr.22','0755236984','kerrsophia@student.com','RO63841588','234','keso','student'),(27,'Pham','Diana','5039411334','Strada Mirelelor nr.99','0756398421','phamdiana@student.com','RO94153262','321','phdi','student'),(28,'Beltran','Diana','5039456788','Strada Cartonului nr.112','0741289653','beltrandiana@student.com','RO35435485','7','beldi','student'),(29,'Penton','Adrian','5023421212','Strada Limbajelor nr.117','0753841296','pentonadrian@student.com','RO3874653','489','pead','student'),(30,'Cortez','Mircea','5039411111','Strada Mehedinti nr.29','0763985412','cortezmircea@student.com','RO7534184','489','comi','student'),(31,'Marcus','Bentley','5039414811','Strada Mehedinti nr.29','0763675145','marcusbentley@profesor.com','RO489456','21','mabe','profesor'),(32,'Fisher','Marius','5039411621','Strada Observatorului nr.215','074562163','fishermarius@profesor.com','RO1563849','4132','fima','profesor'),(33,'Bodescu','Phineas','5039433211','Strada Carcaselor nr.11','0766623346','bodescuphineas@profesor.com','RO213848','12','boph','profesor'),(34,'Marcello','Maria','5039411225','Strada Tranatillo nr.286','0766666546','marmaria@profesor.com','RO484652','252','mama','profesor'),(35,'Insad','Andrei','5039419611','Strada Misterului nr.?','0745836543','insadandrei@profesor.com','RO4566135','43','inan','profesor'),(36,'Ibadescu','Marcus','5039411651','Strada Borhanciului nr.129','0789562345','ibadescumarcus@profesor.com','RO165164874','534','ibma','profesor'),(38,'Mosadar','Vlad','5039416542','Strada Dinerotelor nr.45','0774562765','mosadarvlad@profesor.com','RO4684123','875','movl','profesor'),(39,'Barescu','Cosmin','5039416381','Strada Copcilor nr.11','0735698316','barescucosmin@profesor.com','RO789456','567','baco','profesor'),(40,'Cidronu','Eduard','5034256111','Strada Carapacelor nr.66','0715362135','cidronueduard@profesor.com','RO3498465','56','cied','profesor'),(41,'Caravescu','Mircea','5002569503','Strada Bucuresti nr. 76','0783648039','caravescumircea@admin.com','RO364583958','9502','camir','admin'),(42,'Gemeteanu','Giovanni','5029409116','Strada Carpenterilor nr. 118','0783919705','gemeteanugiovanni@admin.com','RO483648581','9602','gegi','admin'),(45,'Graur','Luca','5001001001','Strada Administratorilor nr, 69a','0724680246','luca25@superadmin.com','RO49306936','419','adminluca','superadmin'),(46,'Iclodean','George','5002002002','Strada Administratorilor nr, 69b','074797479','george22@superadmin.com','RO49306936','421','admingeorge','superadmin'),(47,'Popovici','Andrei','5029593059','Strada Lipscani nr. 5','0784938593','popoviciandrei@student.com','RO75839589','3284','andreipp','student'),(48,'Ionescu','Claudia','5003993849','Strada Stefan cel Mare nr. 7','0736573653','ionescuclaudia@student.com','RO84920394','9022','ioclaud','student'),(49,'Petrescu','Daniela','5019302930','Strada Popesti nr. 45','0748593849','perecudaniela@student.com','RO58395028','9324','patrdan','student'),(50,'Marian','Vlad','5004939384','Strada Calea Oasului nr. 3A','0783958493','marianvlad@student.com','RO48392859','2940','vladmar','student'),(51,'Banc','Sorina','5014950439','Strada Painii nr. 7','0748395024','bancsorina@student.com','RO94830960','9403','sorinaban','student'),(52,'Popa','Cristian','5004930592','Strada Rasaritului nr. 98','0749205844','popacristian@student.com','RO94029490','6505','popacr','student'),(53,'Nistor','Iulia','5024920493','Strada Murgului nr. 67','0784958396','nistoriulia@student.com','RO92058604','2094','nisiul','student'),(54,'Stoica','Margareta','5003859305','Strada Iuliu Maniu nr. 5','0748395729','stoicamarga@student.com','RO09039504','8029','stoima','student'),(55,'Stan','Paul','5002994020','Strada Turda nr. 9','0748392934','stanpaul@student.com','RO20593059','9083','stanp','student'),(56,'Dinu','Paula','5030583920','Strada Aurului nr. 43','0794929505','dinupaula@student.com','RO92049604','1042','dinupau','student'),(57,'Sava','Andrei','5013959305','Strada Casei nr. 5','0793029102','savaandrei@student.com','RO48396049','8921','savana','student'),(58,'Iancu','Tony','5020493056','Strada Laurului nr. 12','0739402952','iancutony@student.com','RO30284094','9021','iancuto','student'),(59,'Hatz','Jon','5019305940','Strada Calea Gurii nr. 8','0782049309','dorianpopahopa@student.com','RO03958392','8543','hatz','student'),(60,'Rusu','Arthur','5003920492','Strada Lupului nr. 20','0739205939','rusuarthur@student.com','RO93859385','3943','rusuar','student'),(61,'Tabacu','Andra','5019403939','Strada Crinului nr. 6','0784029385','tabacuandra@student.com','RO38203958','1892','tabacuan','student'),(62,'Istrate','Silviu','5001885938','Strada Pacii nr. 67','0728481958','istratesilviu@student.com','RO82058395','2190','istsil','student'),(63,'Lupu','Malina','5018859302','Strada Teilor nr. 2','0726471647','lupumalina@student.com','RO29454905','3829','lupumal','student'),(64,'Sava','Traian','5019403950','Strada Oituz nr. 90','0782948109','savatraian@student.com','RO92048202','2101','savatrai','student'),(65,'Cristea','Lorena','5010048024','Strada Crisan nr .5','0732682658','cristealorena@student.com','RO02940294','1820','cristealo','student'),(66,'Pascu','Sorina','5029403950','Strada 1 Mai nr. 67','0783579385','pascusorina@student.com','RO93029503','2894','pascusor','student'),(67,'Tudor','Mark','5020594053','Strada Morii nr. 55','0748392048','tudormark@student.com','RO93029583','2814','tudorma','student'),(68,'Albu','Iulia','5010485930','Strada Eroilor nr. 8','0738294829','albuiulia@student.com','RO28495905','8911','albuiu','student'),(69,'Marin','Ion','5001984859','Strada Traian nr. 1','0738538534','marinion@student.com','RO48395839','1394','marion','student'),(70,'Dobre','Alex','5029504950','Strada Florilor nr. 5','0784921842','dobrealex@student.com','RO49324322','8319','dobal','student'),(71,'Stan','Ioana','5002198531','Strada Rozelor nr. 23','0718374821','stanioana@student.com','RO10492042','3902','stanioa','student'),(72,'Manole','Ana','5019305839','Strada Unirii nr. 8','0738563827','manoleana@student.com','RO39205839','1894','manoan','student'),(73,'Toma','Serban','5001898394','Strada Teilor nr. 5','0784958693','tomaserban@student.com','RO38205832','5446','tomaser','student'),(74,'Voinea','Carmen','5019403952','Strada Horea nr. 3','0728375832','voineacarmen@student.com','RO59204930','8391','voicarme','student'),(75,'Stan','Ion','5029539403','Strada Brad nr. 34','0738394739','stanion@student.com','RO90292049','3281','staio','student'),(76,'Teodor','George','5028593029','Strada Piata Romana nr. 9','0784930284','teogeorge@student.com','RO03950392','8344','teogeo','student'),(77,'Popescu','Ioan','5024930593','Strada Garii nr. 6','0784985839','popescioan@profesor.com','RO68496820','4829','popeioan','profesor'),(78,'Stanciu','Elena','5018483928','Strada Olt nr. 75','0784938593','stanciuelena@profesor.com','RO54431573','5352','stanel','profesor'),(79,'Barbu','Marius','5012849284','Strada Pacii nr. 65','0784850285','barbumarius@profesor.com','RO58490583','6775','barbumar','profesor'),(80,'Moldoveanu','Vlad','5029583956','Strada Teilor nr. 6','0782758375','moldoveanuvlad@profesor.com','RO58593958','2424','moldovla','profesor'),(81,'Sava','Vladimir','5029503953','Strada Izvorului nr. 3','0789544321','savavladimir@profesor.com','RO58394869','4243','savavlad','profesor'),(82,'Iancu','Ilie','5002958395','Strada Zorilor nr. 24','0784938593','iancuilie@profesor.com','RO28499503','4244','iancuili','profesor'),(83,'Manole','Gheorghe','5002892085','Strada Soarelui nr. 64','0784938938','manolegheorghe@profesor.com','RO53819482','7564','manoleghe','profesor'),(84,'Negoita','Alexandra','5004228593','Strada Unirii nr. 76','0782958393','negoitaalexandra@profesor.com','RO58392058','2654','negoialexa','profesor'),(85,'Dobre','Mihaela','5003893482','Strada Lipscani nr. 98','0785213511','dobremihaela@profesor.com','RO48493850','9887','dobmiha','profesor'),(86,'Constantinescu','Sorin','5002586499','Strada G. Cosbuc nr. 2','0784939683','constantinescusorin@profesor.com','RO48492018','2342','constsor','profesor'),(87,'Mocanu','Daniela','5018498395','Strada 1 Decembrie nr. 34','0727858375','moacanudaniela@profesor.com','RO58195839','4244','mocanudan','profesor'),(88,'Moldoveanu','George','5002049503','Strada Kogalniceanu nr. 76','0783294039','moldoveanugeorge@admin.com','RO49583958','9302','moldoge','admin'),(89,'Georgescu','Vasile','5029409305','Strada Eminescu nr. 70','0783959305','georgescuvasile@admin.com','RO48390581','9402','geovas','admin'),(90,'Diaconescu','Bogdan','5004838958','Strada Vladimirescu nr, 55','0783958395','diaconescubogdan@superadmin.com','RO49305930','120','diabogda','superadmin');
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `users_AFTER_INSERT` AFTER INSERT ON `users` FOR EACH ROW BEGIN
	if((select rol from users order by id_user desc limit 1)='student') then
    begin
		insert into studenti (id_student, an, nr_ore) values ((select id_user from users order by id_user desc limit 1), 1, 34);
	end; end if;
    
    if((select rol from users order by id_user desc limit 1)='profesor') then
    begin
		insert into profesori (id_profesor, min_ore, max_ore) values ((select id_user from users order by id_user desc limit 1), 10, 40);
	end; end if;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `users_BEFORE_DELETE` BEFORE DELETE ON `users` FOR EACH ROW BEGIN
	if((select rol from users where id_user = old.id_user)='student') then
    begin
		delete from studenti where id_student = old.id_user;
	end; end if;
    
    if((select rol from users where id_user = old.id_user)='profesor') then
    begin
		delete from profesori where id_profesor = old.id_user;
	end; end if;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-01-19  2:08:24
