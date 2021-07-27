import mindalpha as ma
spark = ma.spark.get_session()
sc = spark.sparkContext

with spark:
    input_path = "s3://{YOUR_S3_BUCKET}/{YOUR_S3_PATH}/example.csv"
    estimator = ma.SwingEstimator(user_id_column_name='_c0',
                                  item_id_column_name='_c1',
                                  behavior_column_name='_c3',
                                  behavior_filter_value='buy',
                                  cassandra_catalog='mycatalog',
                                  cassandra_host_ip='172.17.0.5',
                                  cassandra_port=9042,
                                  cassandra_db_name='testks',
                                  cassandra_table_name='recdb',
                                 )
    dataset = ma.input.read_s3_csv(spark, input_path, delimiter=',')
    model = estimator.fit(dataset)
    model.transform(dataset).show()
    model = model.stringify()
    model.df.show()
    model.publish()
