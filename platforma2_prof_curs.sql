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
-- Table structure for table `prof_curs`
--

DROP TABLE IF EXISTS `prof_curs`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `prof_curs` (
  `id_prof` int DEFAULT NULL,
  `id_curs` int NOT NULL AUTO_INCREMENT,
  `nr_stud` int DEFAULT NULL,
  `id_materie` int DEFAULT NULL,
  `p_seminar` int DEFAULT NULL,
  `p_curs` int DEFAULT NULL,
  `p_lab` int DEFAULT NULL,
  `max_stud` int DEFAULT NULL,
  `seminar` int DEFAULT NULL,
  `curs` int DEFAULT NULL,
  `lab` int DEFAULT NULL,
  PRIMARY KEY (`id_curs`),
  KEY `id_materie` (`id_materie`),
  KEY `id_prof` (`id_prof`),
  CONSTRAINT `prof_curs_ibfk_1` FOREIGN KEY (`id_materie`) REFERENCES `materii` (`id_materie`),
  CONSTRAINT `prof_curs_ibfk_2` FOREIGN KEY (`id_prof`) REFERENCES `profesori` (`id_profesor`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `prof_curs`
--

LOCK TABLES `prof_curs` WRITE;
/*!40000 ALTER TABLE `prof_curs` DISABLE KEYS */;
INSERT INTO `prof_curs` VALUES (36,1,0,1,0,60,10,180,0,1,1),(33,2,1,1,0,10,40,180,0,1,1),(31,3,0,2,50,0,50,80,1,0,1);
/*!40000 ALTER TABLE `prof_curs` ENABLE KEYS */;
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `prof_curs_AFTER_INSERT` AFTER INSERT ON `prof_curs` FOR EACH ROW BEGIN
	update curs_student set nota_finala= (select
    ( select sum(c1) from ((select (select new.p_seminar from prof_curs where prof_curs.id_curs = new.id_curs)*(select avg(nota) as ms from note where note.id_curs = new.id_curs and note.tip_activitate = 'seminar') as c1) UNION
    (select (select new.p_lab from prof_curs where prof_curs.id_curs = new.id_curs)*(select avg(nota) as ms from note where note.id_curs = new.id_curs and note.tip_activitate = 'lab') as c1) UNION
    (select (select new.p_curs from prof_curs where prof_curs.id_curs = new.id_curs)*(select avg(nota) as ms from note where note.id_curs = new.id_curs and note.tip_activitate = 'curs') as c1)
    ) as fin)/100)
    where curs_student.id_curs=new.id_curs;
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `prof_curs_AFTER_UPDATE` AFTER UPDATE ON `prof_curs` FOR EACH ROW BEGIN
	update curs_student set nota_finala= (select
    ( select sum(c1) from ((select (select new.p_seminar from prof_curs where prof_curs.id_curs = new.id_curs)*(select avg(nota) as ms from note where note.id_curs = new.id_curs and note.tip_activitate = 'seminar') as c1) UNION
    (select (select new.p_lab from prof_curs where prof_curs.id_curs = new.id_curs)*(select avg(nota) as ms from note where note.id_curs = new.id_curs and note.tip_activitate = 'lab') as c1) UNION
    (select (select new.p_curs from prof_curs where prof_curs.id_curs = new.id_curs)*(select avg(nota) as ms from note where note.id_curs = new.id_curs and note.tip_activitate = 'curs') as c1)
    ) as fin)/100)
    where curs_student.id_curs=new.id_curs;
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
