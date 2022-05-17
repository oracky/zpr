#!/bin/bash

sqlite3 zpr.db <<EOF
PRAGMA foreign_keys = ON;
create table Cameras (
    camera_id INTEGER PRIMARY KEY,
    x_coordinate REAL,
    y_coordinate REAL,
    visibility_degree REAL
    );
create table Measurements (
    measurement_id INTEGER PRIMARY KEY, 
    vehicle_type INTEGER, 
    x_coordinate REAL, 
    y_coordinate REAL, 
    camera_id INTEGER,
    FOREIGN KEY (camera_id)
       REFERENCES Cameras (camera_id))
EOF