package xyz.productions.phenyl.futuroland.futuroland.Utils;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class Hasher {
    private String hash;
    public Hasher(String str){
        try {
            MessageDigest hasher=MessageDigest.getInstance("SHA-512");
            byte str_bytes[]=hasher.digest(str.getBytes());
            StringBuilder sb=new StringBuilder();
            for (byte str_byte : str_bytes) {
                sb.append(Integer.toString((str_byte & 0xFF) + 0x100, 16).substring(1));
            }
            hash=sb.toString();
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
    }
    public String getHash(){
        return hash;
    }
}
