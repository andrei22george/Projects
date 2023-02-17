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
-- Table structure for table `activitati_grup`
--

DROP TABLE IF EXISTS `activitati_grup`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `activitati_grup` (
  `id_activitate` int NOT NULL AUTO_INCREMENT,
  `id_curs` int DEFAULT NULL,
  `titlu` varchar(45) DEFAULT NULL,
  `data` date DEFAULT NULL,
  `durata` int DEFAULT NULL,
  `nr_min` int DEFAULT NULL,
  `id_prof` int DEFAULT NULL,
  PRIMARY KEY (`id_activitate`),
  KEY `id_curs` (`id_curs`),
  CONSTRAINT `activitati_grup_ibfk_1` FOREIGN KEY (`id_curs`) REFERENCES `prof_curs` (`id_curs`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `activitati_grup`
--

LOCK TABLES `activitati_grup` WRITE;
/*!40000 ALTER TABLE `activitati_grup` DISABLE KEYS */;
INSERT INTO `activitati_grup` VALUES (1,3,'anonimici design','2023-01-17',3,0,31),(2,3,'Anonimici design II','2023-01-17',2,1,NULL),(3,3,'testActivitate','2023-01-18',3,12,31),(4,3,'testActivitate2','2023-01-18',3,12,NULL);
/*!40000 ALTER TABLE `activitati_grup` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-01-19  2:08:24
