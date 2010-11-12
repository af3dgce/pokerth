
package pokerth_protocol;
//
// This file was generated by the BinaryNotes compiler.
// See http://bnotes.sourceforge.net 
// Any modifications to this file will be lost upon recompilation of the source ASN.1. 
//

import org.bn.*;
import org.bn.annotations.*;
import org.bn.annotations.constraints.*;
import org.bn.coders.*;
import org.bn.types.*;




    @ASN1PreparedElement
    @ASN1BoxedType ( name = "AfterHandShowCardsMessage" )
    public class AfterHandShowCardsMessage implements IASN1PreparedElement {
                
        

       @ASN1PreparedElement
       @ASN1Sequence ( name = "AfterHandShowCardsMessage" , isSet = false )
       public static class AfterHandShowCardsMessageSequenceType implements IASN1PreparedElement {
                
        @ASN1Element ( name = "playerResult", isOptional =  false , hasTag =  false  , hasDefaultValue =  false  )
    
	private PlayerResult playerResult = null;
                
  
        
        public PlayerResult getPlayerResult () {
            return this.playerResult;
        }

        

        public void setPlayerResult (PlayerResult value) {
            this.playerResult = value;
        }
        
  
                
                
        public void initWithDefaults() {
            
        }

        public IASN1PreparedElementData getPreparedData() {
            return preparedData_AfterHandShowCardsMessageSequenceType;
        }

       private static IASN1PreparedElementData preparedData_AfterHandShowCardsMessageSequenceType = CoderFactory.getInstance().newPreparedElementData(AfterHandShowCardsMessageSequenceType.class);
                
       }

       
                
        @ASN1Element ( name = "AfterHandShowCardsMessage", isOptional =  false , hasTag =  true, tag = 34, 
        tagClass =  TagClass.Application  , hasDefaultValue =  false  )
    
        private AfterHandShowCardsMessageSequenceType  value;        

        
        
        public AfterHandShowCardsMessage () {
        }
        
        
        
        public void setValue(AfterHandShowCardsMessageSequenceType value) {
            this.value = value;
        }
        
        
        
        public AfterHandShowCardsMessageSequenceType getValue() {
            return this.value;
        }            
        

	    public void initWithDefaults() {
	    }

        private static IASN1PreparedElementData preparedData = CoderFactory.getInstance().newPreparedElementData(AfterHandShowCardsMessage.class);
        public IASN1PreparedElementData getPreparedData() {
            return preparedData;
        }

            
    }
            