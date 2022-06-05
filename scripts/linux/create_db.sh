#!/bin/bash

sqlite3 zpr.db <<EOF
PRAGMA foreign_keys = ON;

CREATE TABLE IF NOT EXISTS Simulations (
    simulation_id INTEGER PRIMARY KEY,
    name TEXT
);
CREATE TABLE IF NOT EXISTS Cameras (
    camera_id INTEGER PRIMARY KEY,
    x_coordinate REAL,
    y_coordinate REAL,
    visibility_degree REAL,
    precision REAL CHECK (precision BETWEEN 0 AND 1)
);
CREATE TABLE IF NOT EXISTS Measurements (
    measurement_id INTEGER PRIMARY KEY, 
    vehicle_type INTEGER, 
    x_coordinate REAL, 
    y_coordinate REAL,
    certainty REAL, 
    camera_id INTEGER,
    simulation_id INTEGER,
    FOREIGN KEY (camera_id)
       REFERENCES Cameras (camera_id),
    FOREIGN KEY (simulation_id)
       REFERENCES Simulations (simulation_id)
);
EOF