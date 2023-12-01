package com.example.registration.credentials;

import jakarta.persistence.Entity;
import jakarta.persistence.Id;
import jakarta.persistence.Table;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;

@Getter
@Entity
@Table
@NoArgsConstructor
@AllArgsConstructor
public class Credentials {
    @Id
    private String username;
    private String password;
}
