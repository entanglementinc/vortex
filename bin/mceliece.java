/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


import de.flexiprovider.api.Registry;
import de.flexiprovider.api.SecureRandom;
import de.flexiprovider.api.keys.KeySpec;
import de.flexiprovider.pki.PKCS8EncodedKeySpec;
import de.flexiprovider.pki.X509EncodedKeySpec;
import de.flexiprovider.pqc.FlexiPQCProvider;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.security.KeyFactory;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.Security;
import javax.crypto.Cipher;

     public static void main(String[] args) throws Exception {
	 
	 Security.addProvider(new FlexiPQCProvider());
	
	 KeyPairGenerator kpg = KeyPairGenerator.getInstance("McEliece","FlexiPQC");
	 kpg.initialize(128);
	 KeyPair keyPair = kpg.generateKeyPair();
	 byte[] encodedPublicKey = keyPair.getPublic().getEncoded();
	 byte[] encodedPrivateKey = keyPair.getPrivate().getEncoded();
       /*  for(byte b : encodedPublicKey)
             System.out.println("Public Key:" + b);
         for(byte d : encodedPrivateKey)
             System.out.println("Private Key:" + d); */
         
        
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Please enter your message : " + "\n");
        String message = null;
        try {
            message = reader.readLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
        //System.out.print("Your message is : " + message + "\n");
        
        //String message = "secret"; 
        byte[] messageBytes = message.getBytes();
        System.out.print("Your message is : " + message + "\n"); 
        KeySpec publicKeySpec = new X509EncodedKeySpec(encodedPublicKey);
 
        KeyFactory keyFactory = KeyFactory.getInstance("McEliece", "FlexiPQC");
        PublicKey publicKey = keyFactory.generatePublic(publicKeySpec);
       // SecureRandom secureRand = Registry.getSecureRandom();
        Cipher cipher = Cipher.getInstance("McEliecePKCS");
        cipher.init(Cipher.ENCRYPT_MODE, publicKey);
        byte[] ciphertextBytes = cipher.doFinal(messageBytes);
        
        for(byte c : ciphertextBytes)
        System.out.print("Your ciphertext is : " + c + "\n");
        
        KeySpec privateKeySpec = new PKCS8EncodedKeySpec(encodedPrivateKey);
        PrivateKey privateKey = keyFactory.generatePrivate(privateKeySpec);
        cipher.init(Cipher.DECRYPT_MODE, privateKey);
        byte[] MessageBytes = cipher.doFinal(ciphertextBytes);
        String Message = new String(MessageBytes);
        System.out.print("Your Message is : " + Message);
        
        

}
