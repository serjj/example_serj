<?php

/**
 * @file
 * All Years Baltics helper class for google spreadsheet import processing.
 */

/* 1.Get Zend GData from here http://framework.zend.com/download/gdata
 * 2.open zip and move the Zend folder from the libary to the same folder as this script
 * 3.update the line at the bottom
 * $gDoc = new gSpreadSheet('GOOGLE ACCOUNT -EMAIL ', 'PASSWORD');
 */

class gSpreadSheet{

  private $gdClient;
  private $currKey;
  private $Cells;

  function __construct($username, $password) {
    //GData setup
    require_once 'Zend/Loader.php';
    Zend_Loader::loadClass('Zend_Http_Client');
    Zend_Loader::loadClass('Zend_Gdata');
    Zend_Loader::loadClass('Zend_Gdata_ClientLogin');
    Zend_Loader::loadClass('Zend_Gdata_Spreadsheets');

    //Login
    //Single-user "installed" client authentication (via HTTP)
    $authService = Zend_Gdata_Spreadsheets::AUTH_SERVICE_NAME;
    $httpClient = Zend_Gdata_ClientLogin::getHttpClient($username, $password, $authService);
    $this->gdClient = new Zend_Gdata_Spreadsheets($httpClient);
  }

  public function ShowWorkSheets() {
    $feed = $this->gdClient->getSpreadsheetFeed();
    return $this->printSS($feed);
  }

  public function printSS($feed){
    $list = array();
    foreach($feed->entries as $k => $entry) {
      if (
        !$entry instanceof Zend_Gdata_Spreadsheets_CellEntry
      &&
        !$entry instanceof Zend_Gdata_Spreadsheets_ListEntry
      ) {
        $list[$k] = $entry->title->text;
      }
    }
    return $list;
  }

  public function getCells($feed) {
    foreach($feed->entries as $entry) {
      if ($entry instanceof Zend_Gdata_Spreadsheets_CellEntry) {
        $this->Cells[$entry->title->text] = $entry->content->text;
      }
    }
  }

  public function getSpreadFeed($id) {
    $feed = $this->gdClient->getSpreadsheetFeed();
    $currKey = explode('/', $feed->entries[$id]->id->text);
    $this->currKey = $currKey[5];
    return $feed->entries[$id]->id->text;
  }

  public function getWorkshets($id) {
    $feed = $this->gdClient->getSpreadsheetFeed();
    $currKey = explode('/', $feed->entries[$id]->id->text);
    $this->currKey = $currKey[5];

    $query = new Zend_Gdata_Spreadsheets_DocumentQuery();
    $query->setSpreadsheetKey($this->currKey);
    $workfeed = $this->gdClient->getWorksheetFeed($query);

    $tabs = array();
    foreach($workfeed->entries as $entry) {
      $worksheetId  = basename($entry->id);  // get the worksheet id
      $title = $entry->title->text;
      $tabs[$worksheetId] = $title;
    }

    return $tabs;
  }

  public function setWorkSheet($id) {
    $this->currWkshtId = $id;
  }

  public function getCell($cell) {
    $cell = strtoupper($cell);
    $query = new Zend_Gdata_Spreadsheets_CellQuery();
    $query->setSpreadsheetKey($this->currKey);
    $query->setWorksheetId($this->currWkshtId);
    $feed = $this->gdClient->getCellFeed($query);
    $this->getCells($feed);
    return $this->Cells[$cell];
  }

  public function getAllCell() {
    $query = new Zend_Gdata_Spreadsheets_CellQuery();
    $query->setSpreadsheetKey($this->currKey);
    $query->setWorksheetId($this->currWkshtId);
    $feed = $this->gdClient->getCellFeed($query);
    $this->getCells($feed);
    return $this->Cells;
  }
}
